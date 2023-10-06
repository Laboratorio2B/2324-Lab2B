#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // necessaria per usare errno


// Esercizio svolto in aula
// Scrivere un programma che legge dalla linea di comando
// il nome di un file di testo contenente valori interi 
// e crea due file con estensione .pari e .dispari
// contenenti rispettivamente gli interi pari e dispari 
// del file originale  



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

  // creo il file con estensione .pari
  char *nomepari = malloc(strlen(nome_file)+6);
  if(nomepari==NULL) termina("Allocazione fallita");
  strcpy(nomepari,nome_file);
  strcat(nomepari,".pari");
  FILE *fp = fopen(nomepari,"wt");
  free(nomepari); // non essendo più necessaria dealloco la stringa 
  if(fp==NULL) termina("Errore creazione file pari");

  // creo il file con estensione .dispari
  char *nomedispari = malloc(strlen(nome_file)+9);
  if(nomedispari==NULL) termina("Allocazione fallita");
  strcpy(nomedispari,nome_file);
  strcat(nomedispari,".dispari");
  FILE *fd = fopen(nomedispari,"wt");
  free(nomedispari); // non essendo più necessaria dealloco la stringa 
  if(fd==NULL) termina("Errore creazione file dispari");

  // leggo tutti gli interi e li riscrivo nel file appropriato
  while(true) {
    int n;
    int e = fscanf(f,"%d",&n);
    if(e==EOF) break;
    if(e!=1) termina("Contenuto illegale nel file");
    if(n%2==0)
      fprintf(fp,"%d\n",n);
    else
      fprintf(fd,"%d\n",n);
  }

  // chiudi tutti i file e termina 
  if(fclose(f)==EOF)
    termina("Errore chiusura file");; 
  if(fclose(fp)==EOF)
    termina("Errore chiusura file");; 
  if(fclose(fd)==EOF)
    termina("Errore chiusura file");; 

  return 0;
}

