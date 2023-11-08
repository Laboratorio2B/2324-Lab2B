/* *********************************************************
 * Esempio di uso di qsort per ordinare array di interi 
 * ********************************************************* */
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <errno.h>    // richiesto per usare errno
#include <string.h>

// stampa un messaggio di errore e termina
void termina(const char *messaggio);


// funzione di confronto, con i tipi corretti
// necessita del casting al tipo __compar_fn_t
// nella chiamata del qsort altrimenti il compilatore
// da un warning
int confronta_str(char **a, char **b)
{
  return strcmp(*a,*b);
}

int main(int argc, char *argv[])
{
  if(argc<=2) {  // input sulla linea di comando non corretto
    printf("Uso: %s str1 str2 str3 ... strk \n",argv[0]);
    return 1;
  }
  int n = argc-1; // Numero argomenti linea di comando

  char **a = &argv[1];

  // stampo array
  for(int i=0;i<n;i++)
    printf("%s ",a[i]);
  puts(""); // a capo 

  // eseguo il sorting degli interi con qsort()
  // come spiegato a lezione per l'ultimo argomento ci vuole il casting  
  qsort(a,n,sizeof(char *), (__compar_fn_t) &confronta_str); 

  // stampo array
  puts("--- qsort eseguito ---");
  for(int i=0;i<n;i++)
    printf("%s ",a[i]);
  puts(""); // a capo 
  
  // a questo punto sarebbe un errore scrivere a[0]
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
