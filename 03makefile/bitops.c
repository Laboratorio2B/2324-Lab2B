#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // richiesto per usare errno

// Scopo del programma:
//  mostrare le operazioni sui bit in C

static void termina(const char *messaggio);


#if 0
&& ||   And e Or logici

a=2
b=9 
a && b -> true


-----
& | ^ bitwise   operazioni tra i bit degli interi 

a =00000011 
b =00001001

a&b -> 00000001
a|b -> 00001011
a^b => 00001010

esiste anche il ~ (not bitwise)
~a = 11111100


<< shift sin
>> shift dex

b = 00001001

c = b<<3 -> 01001000
c>>2 -> 00010010

In C lo shift destro può essere aritmetico o logico
il comportamento è implementation dependent
d = 110000....1
d>>2
  possiamo ottenere 00110000....
  ma anche          1111000000
e = 001000....1 (il bit più significavo è 0)
e>>2 ottengo sempre 00001000...
#endif


// converte il primo intero passato sulla linea di comando in binario
// e il secondo da binario a decimale 
int main(int argc, char *argv[])
{
  // verifica siano stati fornito un parametro 
  if(argc!=3) {
    printf("Uso: %s intero stringa01\n",argv[0]);
    return 1;
  }
  int n = atoi(argv[1]);

  for(int i=31;i>=0;i--) {
    int mask = 1<<i;
    char c = ( (n&mask) !=0  ) ? '1' : '0';
    printf("%c",c);
  }
  puts("");
  
  // convertiamo argv[2] in intero
  // argv[2] = 100011
  n = 0;
  if(strlen(argv[2])>31)
    termina("Stringa in input troppo lunga");
  for(int i=0;i<strlen(argv[2]);i++) {
    if(argv[2][i]=='1') {
      int mask = 1 << ( strlen(argv[2])-i-1  );
      n = n | mask;
    }
    else if(argv[2][i]!='0') 
      termina("Carattere non valido in argv[2]");
  }
  printf("Valore convertito: %d\n",n);
  
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
