#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione ass
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // rischiesto per usare errno
#include <math.h>

// Scopo del programma:
// imparare a costruire, visualizzare e distruggere le liste in C


// prototipi delle funzioni che appaiono dopo il main()
void termina(const char *messaggio);


// definzione struct che rappresenta
// una città con nome, e coordinate 
// + campo next per formare la lista 
typedef struct capit {
  char *nome;
  double lat;
  double lon;
  struct capit *next;
} capitale;


void capitale_stampa(capitale *a, FILE *f) {
  fprintf(f,"%20s (%f,%f)\n",a->nome,a->lat,a->lon);
}


capitale *capitale_crea(char *s, double lat, double lon)
{
  capitale *a  = malloc(sizeof(*a));
  a->lat = lat;
  a->lon = lon;
  a->nome = strdup(s); // creo una copia di s e l'assegno al nome
  a->next = NULL;
  return a;
}

void capitale_distruggi(capitale *a)
{
  free(a->nome);
  free(a);
}

// stampa tutti gli elementi della lista lis
void lista_capitale_stampa(capitale *lis, FILE *f)
{
  capitale *p = lis;  // se ne puo' fare a meno
  while(p!=NULL) {
    capitale_stampa(p,f);
    p = p->next;
  }
  return;
}

// distrugge tutti gli elementi della lista lis
void lista_capitale_distruggi(capitale *lis)
{
  while(lis!=NULL) {
    capitale *tmp = lis->next; // necessario
    capitale_distruggi(lis);
    lis = tmp;
  }
  return;
}


// legge un oggetto capitale dal file f
// restituisce il puntatore all'oggetto letto
// oppure NULL se non riesce a leggere dal file
capitale *capitale_leggi(FILE *f)
{
  assert(f!=NULL);
  char *s;
  double lat, lon;
  int e = fscanf(f,"%ms %lf %lf",&s,&lat,&lon);
  if(e!=3)
     return NULL;
  capitale *c = capitale_crea(s,lat,lon);
  free(s);
  return c;
}

// crea una lista con gli oggetti capitale letti da 
// *f inserendoli ogni volta in testa alla lista
capitale *crea_lista_testa(FILE *f)
{
  // costruzione lista leggendo capitali dal file
  capitale *testa=NULL;
  // capitale *coda=NULL;  // serve per l'inserimento in coda
  while(true) {
    capitale *b = capitale_leggi(f);
    if(b==NULL) break;
    // inserisco b in testa alla lista
    b->next = testa;
    testa = b;
  }  
  return testa;
}

// inserisce elemento "c" in lista "testa" 
// mantenendo ordinamento per latitudine decrescente
capitale *inserisci_lat(capitale *testa, capitale *c)
{
  assert(c!=NULL); // devo avere un oggetto da inserire
  
  // tratta il caso testa==NULL (lista vuota)
  if(testa==NULL) {
    c->next = NULL;  // creo lista con solo c
    return c;        // e la restituisco
  }
  
  assert(testa!=NULL);  // caso lista non vuota
  // verifico se c va messo prima di tutti 
  if(c->lat > testa->lat) {
    c->next = testa; // c va messa in testa
    testa = c;
    return testa; 
  }
  
  // ora so che c deve essere inserito dopo il primo elemento
  // questo implica che il primo elemento rimane quello 
  // a cui punta testa (quindi terminerò con return testa)
  capitale *p = testa;
  while(p->next!=NULL) {
    // controllo se c va inserito tra p e p->next
    assert(c->lat <= p->lat); 
    if(c->lat > p->next->lat) {
      // inserire c tra p e p->next
      c->next = p->next;
      p->next = c;
      // citta inserita posso terminare
      return testa;
    }
    p = p->next; // considero il prossimo elemento della lista
  }
  assert(p->next==NULL);
  // c va inserita in fondo
  p->next = c;
  c->next = NULL;
  return testa;
} 




int main(int argc, char *argv[])
{

  if(argc!=2) {
    printf("Uso: %s nomefile\n",argv[0]);
    exit(1);
  } 
  FILE *f = fopen(argv[1],"r");
  if(f==NULL) termina("Errore apertura file");

  // costruzione lista leggendo capitali dal file
  capitale *testa=crea_lista_testa(f);
  puts("--- inizio lista ---");
  // stampa lista capitali appena creata
  lista_capitale_stampa(testa,stdout);  
  puts("--- fine lista ---");
  
  
  if(fclose(f)==EOF)
    termina("Errore chiusura");
  
  // dealloca la memoria usata dalla lista 
  lista_capitale_distruggi(testa);
  
  return 0;
}



// stampa su stderr il  messaggio che gli passo
// se errno!=0 stampa anche il messaggio d'errore associato 
// a errno. dopo queste stampe termina il programma
void termina(const char *messaggio)
{
  if(errno==0) 
     fprintf(stderr,"%s\n",messaggio);
  else 
    perror(messaggio);
  exit(1);
}

