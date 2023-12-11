
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

**Lezione 7** (10/10/23)

* Equivalenza fra `*a` e `a[0]`
* Equivalenza fra `a` e `&a[0]`, significato di `&a[i]`
* Aritmetica dei puntatori: definizione di `a+i` come `&a[i]`
* Significato del tipo `const char *` 
* Calcolo lunghezza di una stringa usando l'aritmetica dei puntatori
* Esempio di uso dell'aritmetica dei puntatori nel *mergesort*


-----

**Lezione 8** (18/10/23)

* Lettura di stringhe con `scanf`:  problematica del [buffer overflow](https://en.wikipedia.org/wiki/Buffer_overflow)
* Evitare il buffer overflow: modificatori `%Ns` (con N massimo numero di caratteri) e `%ms`
* Costruzione di stringhe mediante `asprintf` 
* Esercitazione in aula

-----

**Lezione 9** (19/10/23)

* definizione di tipi composti con `struct`
* definizione di nuovi tipi con `typedef` e uso combinato con `struct`
* operazioni sui tipi composti, notazioni `.` e  `->`
* esercizi e discussione uso di Copilot

-----

**Lezione 10** (20/10/23)

Prova in itinere su array e file in C 

-----

**Lezione 11** (24/10/23)

* Array di puntatori a struct, esempio: array di capitali
* Ordinamento array di puntatori a struct mediante mergesort

---

**Lezione 12** (27/10/23)

* Introduzione all'uso delle funzioni come parametri di altre funzioni
* Mergesort con funzione di confronto passata come argomento
* Introduzione alle *linked list*: creazione, stampa, distruzione di liste

---

**Lezione 13** (31/10/23)

* Costruzione di liste con inserimento in testa, in coda e ordinato
* Funzione ricorsiva per l'inserimento da una lista
* Cancellazione da una lista utilizzando la ricorsione: versione iterativa da fare per esercizio

---


**Lezione 14** (3/11/23)

* Lettura da file con getline()
* Parsing di stringhe mediante strtok()
* Variabili statiche
* Esercizio in aula su liste di interi (Fibolista)

----

**Lezione 15** (7/11/23)

* Funzionamento interno di strtok()
* Variabili statiche
* File oggetto (`.o`), compilazione separata
* Uso del makefile: target, prerequisiti, comandi

----

**Lezione 16** (7/11/23)

* Ancora sul makefile: lazy evaluation, variabili, variabili automatiche, e regole implicite.
* Puntatori generici (`void *`). 
* Funzione di libreria `qsort`.
* Sorting di interi, funzione di confronto, casting.

----

**Lezione 17** (8/11/23)

* Ancora su `qsort` e casting.
* Sorting di stringhe con `qsort`
* Esercizio in aula su qsort (qTriple)

---

**Lezione 18** (14/11/23)

* Matrici in C, statiche e dinamiche. 
* Accesso a sistemi remoti via ssh con X11 forwarding
* Uso di gdbgui per debugging su sistemi remoti attraverso un browser.
* Uso di un debugger: esecuzione passo/passo, accesso alle variabili breakpoint condizionali. Visualizzazione registri ARM e loro uso nei breakpoint condizionali. 
* Esempio test di primalita in assembler ARM


---

**Lezione 19** (17/11/23)

 
* Operatori bitwise `&`, `|`, `^`, `~`, <<`, `>>`.
* Scrittura su file binari in C; comando `od`
* Implementazione `strcmp` in assembler ARM

---

**Lezione 20** (21/11/23)

* Lettura da file binari in C. Funzioni `fseek` e `ftell`.
* Implementazione funzione di libreria `strtok` in C e in assembler ARM. 
* Compilazione condizionale: `#ifdef`-`#endif` 
* Uso di pattern rule nel makefile 

---

**Lezione 21** (24/11/23)

* Seconda prova in itinere

---

**Lezione 22** (28/11/23)

Introduzione a Python, differenze e similarità con il C. 
Sintassi, interprete, istruzioni `if`, else`, `elif`, `for`, `while`. Definizione di funzioni. Liste.


---

**Lezione 23** (11/12/23)

Python: Dizionari, DocString ed esecuzione dalla linea di programma.  
Esempio: costruzione classifica leggendo risultati da file. Uso di `import` e `sys.argv`. Apertura di file con `with` e `open`. Istruzione `raise` per segnalare gli errori. Sorting di liste utilizzando una key function. 



