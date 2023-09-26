#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe

// le istruzioni qui sopra le spieghiamo più avanti 

// da compilare con:
//  gcc -std=c11 -Wall -O -g -o primi  primi.c


// Scopo del programma:
//  legge un intero N da tastiera
//  crea un array *dinamico* con i primi <=N

// prototipo della funzione primo()
// bool primo(int k);
// non necessario in quanto la definizione è prima del main


// dato k restituisco True se è primo, false altrimenti
// suggerito da copilot
bool isprime(int k) {
  // se k è pari e diverso da 2 allora non è primo
  if(k%2==0 && k!=2) return false;
  // se k è dispari e non è primo
  // allora esiste un divisore <= sqrt(k)
  // che è dispari
  // quindi posso controllare solo i divisori dispari
  // e posso fermarmi a sqrt(k)
  for(int i=3; i*i<=k; i+=2) {
    if(k%i==0) return false;
  }
  return true;
}




// stampa un messaggio d'errore e termina il programma
void termina(char *messaggio)
{
  puts(messaggio);
  exit(1);
}



int main(int argc, char *argv[])
{
  int n; // definisco variabile intera di nome n

  // spiego cosa voglio leggere e lo leggo con scanf  
  printf("Inserisci il valore N: ");
  int *m = &n;
  int e = scanf("%d",m); // il motivo della & lo vedremo più avanti 
  // controlli sulla lettura
  if(e!=1) termina("Valore non trovato");
  if(n<2)  termina("Non ci sono numeri primi");
  
  
  // crea un array dinamico inizialmente di 10 elementi
  int *a;  // dichiaro che a sarà usata come array
  int size = 10;   // dimensione attuale dell'array
  int messi = 0;   // numero di elementi attualmente dentro l'array 
  a = malloc(size*sizeof(int));
  if(a==NULL) 
    termina("Malloc fallita");


  // riempio array
  for(int i=2; i<=n; i++) {
    if(primo(i)) {
      // se l'intero i è primo lo inserisco
      // nella tabella dei primi
      // ma prima verifico che ci sia spazio
      if(messi==size) {
        size = 2*size; // se la tabella è piena raddoppio la dimensione
        a = realloc(a,size*sizeof(int));
        if(a==NULL)
          termina("Realloc fallita");
      }
      // inserisco il primo i dentro a[]
      a[messi] = i;
      messi += 1;
    }
  }
  // tabella completata
  // riduco array alla dimensione minima
  a = realloc(a,messi*sizeof(int));
  if(a==NULL) termina("Realloc fallita");
    
  // stampa contenuto array, usando 8 caratteri per intero 
  for(int i=0;i<messi;i++) {     
    printf("%8d",a[i]);                    
  }
  printf("\n");
  // dealloco la memoria della tabella
  free(a);
  return 0;
}




