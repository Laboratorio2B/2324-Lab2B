#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // rischiesto per usare errno

// prototipi delle funzioni che appaiono dopo il main()
void termina(const char *messaggio);

// Scopo del programma:
// Mostrare come si definiscono e usano le struct


// keyword typedef: per definire sinonimi di tipi esistenti
// ad esempio posso metetre le istruzioni (fuori da ogni funzione)
typedef int intero;
typedef int *puntatore_a_int;
// e nel resto del programma posso scrivere "intero" invece di "int"
// e "puntatore_a_int" invece di "int *"


// E' molto frequente l'uso combinato di struct 
// (definisce nuovi tipi) e typdef (definisce un sinonimo)
// Esempio: definisco la struct duetto
// dico che coppia è sinonimo di struct duetto
typedef struct duetto {
  int primo;
  int secondo;
} coppia;
// nel resto del programma posso usare liberamente "coppia" o "struct duetto"


// scambia le componenti: il parametro d è passato per valore 
// quindi la funzione opera su una copia locale di d
// e la modifica non ha effetto sul chiamante
struct duetto scambia(struct duetto d)
{ 
  intero tmp = d.primo;
  d.primo = d.secondo;
  d.secondo = tmp;
  return d;
}

// stampa su f la coppia passata per valore 
void coppia_stampa(coppia a, FILE *f) {
  fprintf(f,"(%d,%d)\n",a.primo,a.secondo);
}

// stampa su f la coppia passata per indirizzo
// const indica che la funzione non può modificare
// la coppia a cui punta il parametro a
// si passa il parametro per indirizzo per evitare di fare 
// una copia della struct da stampare che potrebbe essere 
// molto grande (in questo caso no: sono solo 2 interi)
void pcoppia_stampa(const coppia *a, FILE *f) {
  fprintf(f,"(%d,%d)\n",(*a).primo,(*a).secondo);
}

// incrementa di 1 entrambe le componenti della coppia
// il parametro a è passato per indirizzo
// quindi la funzione modifica la coppia a cui punta a
void incrementa(coppia *a) {
  (*a).primo +=1;   // come visto ao lezione le parentesi sono necessarie
  a->secondo +=1; // l'uso di a-> al posto di (*a). è equivalente e molto usato
}


// esempio di costruzione di un array di coppie e di uso delle funzioni
// viste sopra
int main(int argc, char *argv[])
{
  coppia *a;

  if(argc <3 || argc%2==0) {
    printf("Uso: %s un numero positivo pari di interi\n",argv[0]);
    exit(1);
  } 
  int n = (argc-1)/2;  // dimensione di a  == numero coppie
  a = malloc(n*sizeof(coppia));
  if(a==NULL) termina("allocazione fallita");

  // crea l'array e incrementa di 1 entrambe le componenti di ogni coppia
  for(int i=0;i<n;i++) {
    a[i].primo = atoi(argv[2*i+1]);
    a[i].secondo = atoi(argv[2*i+2]);  
    incrementa(&a[i]); // passaggio per riferimento!
  }

  // stampa le coppie: uso entrambe le funzioni di stampa
  // di solito si definisce e si usa solo quella che stampa per indirizzo  
  for(int i=0;i<n;i++)
   if(i%2==0)
      coppia_stampa(a[i], stdout);
    else   
      pcoppia_stampa(&a[i], stdout);

  // abbiamo allocato a[] quindi dobbiamo deallocarlo
  free(a);
  return 0;
}


// stampa su stderr il messaggio che gli passo
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

