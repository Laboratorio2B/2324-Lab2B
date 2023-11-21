#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe



// emulazione della funzione strtok in assembler o in C
char *miatok(char *s, int delim);


// tokenizza la stringa passata in argv[1]
int main(int argc, char *argv[])
{
  if(argc==2) {
    char *tok = miatok(argv[1],',');
    while(tok!=NULL) {
      puts(tok);
      tok = miatok(NULL,',');
    }
    // verifico che anche la successiva chiamata a miatok restituisca NULL
    assert(miatok(NULL,',')==NULL);
  }
  else 
    printf("Uso: %s stringa\n",argv[0]);
  return 0;
}

#ifdef NOARM
char *miatok(char *s, int d)
{
  static char *ultimapos = NULL;
  
  if(d==0) termina("Separatore illegale");
  // riprende tokenizzazione precedente
  if(s==NULL)
    s = ultimapos;
  if(s==NULL)
    return NULL;
    
  // la stringa contiene qualcosa
  // salto eventuali caratteri = d
  while(*s==d)
    s += 1;  // avanzo nella stringa 

  // ora c'è qualcosa diverso dal delimitatore
  assert(*s!=d);
  if(*s=='\0') {  // sono in fondo alla stringa?
    ultimapos = NULL; // non fare altre chiamate su questa stringa
    return NULL;
  }
  assert(*s!='\0' && *s!=d);
  // c'è un token che inizia in s
  char *t = s;
  for(  ;*t!=d; t++)
    if(*t=='\0') { // siamo arrivati a fine stringa
      ultimapos = NULL; 
      return s;
    }
  // ho trovato un carattere uguale a d
  assert(*t == d);
  *t = '\0';         // sovrascrivo il delimitatore con \0
  ultimapos = t + 1; // puntatore a carattere dopo \0
  return s;
}
#endif


