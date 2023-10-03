#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // necessaria per usare errno


// Scopo del programma:
//  mostrare come si legge da un file di testo 


// stampa un messaggio d'errore su stderr e termina il programma
void termina(char *messaggio)
{
  // se errno!=0 oltre al mio messaggio stampa il messaggio
  // associato alla variabile globale errno 
  // utilizzando la funzione di libreria perror()
  if(errno!=0) perror(messaggio);
  // altrimenti stampa solo il mio messaggio
  else fprintf(stderr,"%s\n", messaggio);
  exit(1);
}

// legge gli interi che sono nel file f
// e li salva in un array che viene restituito
// con return + passaggio per riferimento
int *leggi_file(FILE *f, int *num_elementi)
{
  assert(f!=NULL); // il file deve essere valido
  int size=10; // dimensione attuale dell'array
  int messi=0; // numero di elementi attulamente nell'array
  int *a = malloc(size*sizeof(int));
  if(a==NULL)
    termina("Memoria insufficiente");
    
  while(true) {
    int n;
    int e = fscanf(f,"%d",&n);
    if(e==EOF) break;
    if(e!=1) termina("Contenuto illegale nel file");
    // ho letto un intero dal file ed è stato messo in n
    if(messi==size) {
        // ingrandisco l'array
        size = size*2;
        a = realloc(a,size*sizeof(int));
        if(a==NULL)
          termina("realloc fallita");
    }
    assert(size>messi);
    a[messi] = n;
    messi += 1;
  }
  // ho messo tutti gli elementi che mi interessavano
  size = messi;
  a = realloc(a,size*sizeof(int));
  if(a==NULL)
    termina("realloc fallita");  
  // salvo il numero di elementi e restituisco l'array  
  *num_elementi = messi;
  return a;  
} 

// visualizza elementi array di un qualsiasi 
// array di int sul terminale
void stampa_array(int *a, int n)
{
  assert(a!=NULL);
  // stampo il contenuto dell'array
  for(int i=0;i<n;i++)
    fprintf(stdout,"%8d",a[i]); // stampo gli elementi in un campo di 8 caratteri
  fprintf(stdout,"\nIn totale l'array contiene %d interi\n",n);
  fprintf(stderr,"Ho finito!\n");
}


int main(int argc, char *argv[])
{
  // verifica siano stati forniti esattamente 2 parametri 
  if(argc!=2) {
    printf("Uso: %s nome_file\n",argv[0]);
    return 1;
  }
  // copia il puntatore nella variabile nome_file
  char *nome_file = argv[1];
  
  // apro il file in lettura 
  FILE *f = fopen(nome_file,"rt");
  if(f==NULL) termina("Apertura file fallita");

  int n; // numero di elementi nell'array
  int *a = leggi_file(f,&n);

  // stampo gli elementi dell'array
  stampa_array(a,n);
  free(a);

  // chiudi il file e termina 
  if(fclose(f)==EOF)
    termina("Errore chiusura file");; 
   
  return 0;
}

