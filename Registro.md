
##  Introduzione ad array, puntatori e file (introC)


**Lezione 1** (19/9/23)

* Introduzione al linguaggio C. Esempio di lettura e scrittura di interi dal terminale. Compilazione. Esecuzione di programmi 

-----------------------

**Lezione 2** (22/9/23)

* Allocazione dinamica di array in C. Funzioni: malloc/free/realloc. 
* Utilizzo di *valgrind* per verificare il corretto utilizzo degli array

-------

**Lezione 3** (26/9/23)

* Introduzione ai puntatori
* Significato e uso di `*` e `&`
* Esempio passaggio parametri per riferimento

-------

**Lezione 4** (29/9/23)

* Ancora sui puntatori, passaggio di parametri alle funzioni per riferimento
* Rappresentazione di stringhe in C
* introduzione al *makefile*; compilazione con il comando *make*

-----

**Lezione 5** (3/10/23)

* Uso dei parametri argc/argv di main()
* Copia di un puntatore vs copia di un array: la funzione strdup()
* Scrittura in un file di testo: fopen(), fprintf(), fclose()
* Terminazione in caso di errori: funzione perror() e variabile globale `errno`


-----

**Lezione 6** (6/10/23)

* Lettura e scrittura da file. Modalità *append* 
* Comando `od` per visualizzare il contenuto di un file
* Uso di asserzioni
* Esempio lettura di un array di interi da un file
* stdout/stderr/stdin e loro ridirezione; esempi
* Esercizio in aula (`dividi.c`)

----

**Lezione 7** (10/11/23)

* Equivalenza fra `*a` e `a[0]`
* Equivalenza fra `a` e `&a[0]`, significato di `&a[i]`
* Aritmetica dei puntatori: definizione di `a+i` come `&a[i]`
* Significato del tipo `const char *` 
* Calcolo lunghezza di una stringa usando l'aritmetica dei puntatori
* Esempio di uso dell'aritmetica dei puntatori nel *mergesort*


-----

**Lezione 8** (17/11/23)

* Lettura di stringhe con `fscanf`:  problematica del [buffer overflow](https://en.wikipedia.org/wiki/Buffer_overflow)
* Evitare il buffer overflow: modificatori `%Ns` (con N massimo numero di caratteri) e `%ms`
* Mergesort di stringhe 
* Costruzione di stringhe mediante `asprintf` 