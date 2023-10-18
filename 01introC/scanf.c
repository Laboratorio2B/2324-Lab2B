#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // rischiesto per usare errno


// scopo del programma:
// mostrare le opzioni di come leggere delle stringhe con 
// fscanf (e simili, tipo fscanf) 
// Fare riferimento ai lucidi dentroScanf.pdf

// Ricordare che l'uso di scanf("%s"...) è un'operazione
// a rischio di buffer overflow in quanto
// è possibile scrivere in zone esterne a quelle allocate al programma


// stampa un messaggio d'errore su stderr e termina il programma
void termina(const char *messaggio);


int main(int argc, char *argv[])
{
  int a=1;
  char s[12];
  char *z=NULL;
  puts("Inserisci un numero e due stringhe"); 
  int e = scanf("%d %11s %ms",&a,s,&z);
  if(e!=3) termina("Errore scanf");

  printf("a=%d,s=%s,z=%s\n",a,s,z);  

  // libero memoria allocata da scanf
  free(z);

  // %11s garantisce che vengono letti al più 12 caratteri (11+\0)
  // e quindi rimaniamo dentro s[12]  
  
  // %ms delega il compito di allocare la memoria a scanf
  // devo ricordarmi il passaggio per riferimento 
  // e di eseguire la free() quando la stringa non è più necessaria
  
  
  return 0;
}



void termina(const char *messaggio)
{
  // se errno!=0 oltre al mio messaggio stampa il messaggio
  // associato alla variabile globale errno 
  // utilizzando la funzione di libreria perror()
  if(errno!=0) perror(messaggio);
  // altrimenti stampa solo il mio messaggio
  else fprintf(stderr,"%s\n", messaggio);
  exit(1);
}

