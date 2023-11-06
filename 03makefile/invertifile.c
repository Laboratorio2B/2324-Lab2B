#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa exit() etc ...
#include <stdbool.h>  // gestisce tipo bool
#include <assert.h>   // permette di usare la funzione ass
#include <string.h>   // funzioni per stringhe
#include <errno.h>    // richiesto per usare errno
// #include <ctype.h> 

// reversefile
// legge  tutte le linee da un file di testo e le
// stampa su stdout in ordine inverso
// 


#include "listastringhe.h"


// prototipi delle funzioni che appaiono dopo il main()
void termina(const char *messaggio);



int main(int argc, char *argv[])
{

  if(argc!=2) {
    printf("Uso: %s nomefile\n",argv[0]);
    exit(1);
  } 
  FILE *f = fopen(argv[1],"r");
  if(f==NULL) termina("Errore apertura file");


  // costruzione lista leggendo citta dal file
  stringola *linee=NULL;
  // ciclo di lettura dal file
  size_t n=0;
  char *buffer=NULL;
  while(true) {
    ssize_t e = getline(&buffer,&n,f);
    if(e<0) break;
    // crea stringa con linea del file
    stringola *s = stringola_crea(buffer);
    // aggiunge in testa alla lista
    s->next = linee;
    linee = s;
  }
  free(buffer);
  if(fclose(f)!=0) termina("Errore chiusura file");
  lista_stringola_stampa(linee,stdout);
  // dealloco la lista e termino
  lista_stringola_distruggi(linee);
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


