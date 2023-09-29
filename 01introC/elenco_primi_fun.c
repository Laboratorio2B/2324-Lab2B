#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe

// le istruzioni qui sopra leggono i prototipi di alcune funzioni di libreria

// da compilare con:
//  gcc -std=c11 -Wall -O -g -o elenco_primi_fun elenco_primi_fun.c


// Scopo del programma:
//  mostrare come si dichiarano e utilizzano le funzioni che 
//  hanno degli array come parametri di input e/o output



// prototipo della funzione primo()
// bool primo(int k);
// non necessario in quanto la definizione è prima del main



// dato k restituisco true se è primo, false altrimenti
bool primo(int k)
{
  if(k%2==0)
    return k==2;
  // era uguale scrivere
  //   if(k==2) return true;  
  //   else return false;
  // ma scrivere return k==2 è più breve e (per me) più chiaro  

  // mi occupo del caso k dispari
  for(int i=3; i<k; i+=2 ) {
    if(k%i==0) return false; // ho scoperto che il numero non è primo
    if(i*i>k) break;
  }
  return true;
}


// stampa un messaggio d'errore e termina il programma
void termina(char *messaggio)
{
  puts(messaggio);
  exit(1);
}

// input: intero n
// output: array dei primi <=n
int *elenco_primi(int n, int *p)
{
  
  printf("Valore di p: %ld\n", (long) p);
  printf("Valore a cui punta p: %d\n", *p);
  
  // crea un array dinamico inizialmente di 10 elementi
  int *a;  // dichiaro che a sarà usata come array
  int size = 10;   // dimensione attuale dell'array
  int messi = 0;   // numero di elementi attualmente dentro l'array 
  a  = malloc(size*sizeof(int));
  if(a==NULL) termina("Malloc fallita");

  // riempio array
  for(int i=2; i<=n; i++) {
    if(primo(i)) {
      // se l'intero i è primo lo inserisco
      // nella tabella dei primi
      // ma prima verifico che ci sia spazio
      if(messi==size) {
        size = 2*size; // se la tabella è piena raddoppio la dimensione
        a = realloc(a,size*sizeof(int));
        if(a==NULL) termina("Realloc fallita");
      }
      // inserisco il numero primo i dentro a[]
      a[messi] = i;
      messi += 1;
    }
  }
  // tabella completata
  // riduco array alla dimensione minima
  a = realloc(a,messi*sizeof(int));
  if(a==NULL) termina("Realloc fallita");
  *p = messi;  // va a scrivere in quanti 
               // la dimensione dell'array
  return a;
}


// funzione che stampa l'array che inizia in b
// e contiene k elementi
void stampa_array_int(int b[], int k)
{
  // stampa contenuto array, usando 8 caratteri per intero 
  for(int i=0;i<k;i++) {     
    printf("%8d",b[i]);                    
  }
  printf("\nNumero di elementi: %d\n", k);
}


int main(int argc, char *argv[])
{
  int n; // definisco variabile intera di nome n

  // spiego cosa voglio leggere e lo leggo con scanf  
  printf("Inserisci il valore N: ");
  int e = scanf("%d",&n); // il motivo della & lo vedremo più avanti 
  // controlli sulla lettura
  if(e!=1) termina("Valore non trovato");
  if(n<2)  termina("Non ci sono numeri primi");
  
  // i primi verranno messi nell'array a[] che
  // avra' `quanti` elementi
  int *a;
  int quanti=1234321; // valore random sarà sovrascritto
  printf("Indirizzo di quanti: %ld\n", (long) &quanti);
  a = elenco_primi(n, &quanti);
  // magicamente (cioè usando il puntatore) la funzione 
  // elenco_primi scrive in quanti la dimensione dell'array

  // stampo elementi di a[] 
  stampa_array_int(a,quanti); 

  // dealloco la memoria dell'array dei primi
  free(a);
      
  return 0;
}

