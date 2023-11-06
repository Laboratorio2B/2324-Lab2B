#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione ass
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // richiesto per usare errno

void termina(const char *messaggio);

// definizione struct che rappresenta
// un elemento di una lista di stringhe
typedef struct stringola {
  char *str;
  struct stringola *next;
} stringola;


// solite funzioni per creazione, distruzione, stampa della lista
stringola *stringola_crea(char *s)
{
  stringola *a  = malloc(sizeof(*a));
  a->str = strdup(s); // creo una copia di s e l'assegno al nome
  a->next = NULL;
  return a;
}

void stringola_distruggi(stringola *a)
{
  free(a->str);
  free(a);
}

void stringola_stampa(stringola *a, FILE *f) {
  fprintf(f,"%-20s\n",a->str);
}

void lista_stringola_stampa(stringola *lis, FILE *f)
{
  while(lis!=NULL) {
    stringola_stampa(lis,f);
    lis = lis->next;
  }
}

void lista_stringola_distruggi(stringola *lis)
{
  if(lis!=NULL) {
    lista_stringola_distruggi(lis->next);
    stringola_distruggi(lis);
  }
}

// input lis: lista di stringole può essere vuota 
//             ma deve essere ordinata lessicograficamente
//          c: stringola da inserire deve eiustere c!=NULL
//  outpu:t la nuova lista con c inserita matenendo l'ordine
stringola *lista_stringola_inserisci_lex(stringola *lis, stringola *c) 
{
  assert(c!=NULL);
  if(lis==NULL) {
    c->next = NULL;
    return c;
  }
  if(strcmp(c->str,lis->str)<0) {
    // il nome in c è il più piccolo
    // diventa lui il primo elemento
    c->next = lis;
    return c;
  }
  else {
    // lis rimane il primo elemento, quindi restituisco lui
    // seguito dal resto della lista in cui la ricorsione
    // ha piazzato c al posto giusto
    lis->next = lista_stringola_inserisci_lex(lis->next,c);
    return lis;
  }
}


// "elimina" gli spazi in testa a una stringa
// restituisce un puntatore alla prima posizione
// che non è uno spazio
char *elimina_spazi_testa(char s[])
{
  int i=0;
  while(s[i]==' ')
    i++;
  assert(s[i]!=' ');
  return &s[i];
}


// main che legge le linee e le spezza al ;
// poi inserisce le stringhe in una lista ordinata
int main(int argc, char *argv[])
{

  if(argc!=2) {
    printf("Uso: %s nomefile\n",argv[0]);
    exit(1);
  } 
  FILE *f = fopen(argv[1],"r");
  if(f==NULL) termina("Errore apertura file");

  // costruzione lista stringhe leggendo dal file
  // ogni linea del file puo' contenere piu' stringhe
  // le stringhe posso contentenere degli spazi
  stringola *lista=NULL;  // lista vuota
  // ciclo di lettura dal file f
  char *buffer=NULL;    // usate da getline()
  size_t n=0;
  while(true) {
    //leggi linea dal file
    ssize_t e = getline(&buffer,&n,f);
    if(e<0) { // assumiamo sia finito il file
      free(buffer);  // dealloco il buffer usate per contenere le linee 
      break;  
    }
    // fprintf(stderr,"n=%zd, buffer=%s",n,buffer);
    // esegue il parsing di buffer 
    char *s = strtok(buffer,";\n");
    while(s!=NULL) {
      s = elimina_spazi_testa(s);
      if(s[0]!='\0') {
        stringola *c = stringola_crea(s);
        // aggiungo la stringa alla lista
        lista = lista_stringola_inserisci_lex(lista,c);
      }
      s = strtok(NULL,";\n");
    }
    // ho messo tutte le stringhe date da strtok
  } // end while del getline
  fclose(f);
  lista_stringola_stampa(lista,stdout);
  lista_stringola_distruggi(lista);
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



