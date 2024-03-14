
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


---

**Lezione 24** (30/1/24)

Definizione e uso di classi in python. I metodi speciali `__init__`,  `__eq__`,  `__repr__`,  ` __str__`,  `__lt__`. Variabili e metodi statici. Sottoclassi. 

---

**Lezione 25** (6/2/24)

Uso del decorator `@functools.total_ordering` su una classe. Metodi speciali per operatori aritmetici (`__add__`, `__mul__`, etc.). Esplorazione del filesystem in Python: metodi dei moduli `os` e `os.path`.  Concetti di [link symbolici](https://linuxize.com/post/how-to-create-symbolic-links-in-linux-using-the-ln-command/) e di [permessi](https://linuxcommand.org/lc3_lts0090.php). 


---

**Lezione 26** (8/2/24)

Ancora sull'esplorazione del filesystem in Python. I tipi [`set`](https://docs.python.org/3/library/stdtypes.html#set) e [`dict`](https://docs.python.org/3/library/stdtypes.html#dict). Ricerca dei file modificati più di recente. 


--- 

**Lezione 27** (13/2/24)

Invocazione comandi della shell da python con `subprocess.run`.
Ricerca di file duplicati in python . I metodi `__eq__` e `__hash__`

---

**Lezione 28** (15/2/24)

System calls vs library functions.
Sezioni del system manual (comando man).
Esempi: open/read/write vs fopen/fread/fwrite/fprintf
Significato e uso di `umask`
Esempio prestazioni di `write` vs `fwrite`.
Creazione di processi in C: comando `fork`.
Comandi del terminale `ps` e `htop`


---

**Lezione 29** (16/2/24)

Gestione degli errori: xerrori.c e xerrori.h
Comandi `wait` e `sleep`, processi zombie. 
Processi e linea di comando: utilizzo di `kill` e `&`
Concetto di pipe per la comunicazione fra processi. 

---

**Lezione 30** (20/2/24)

Primi esempi di pipe: programmi `contaprimi` e `contaprimifile`.  Documentazione sulle pipe, pagine: pipe(2) pipe(7).


---

**Lezione 31** (22/2/24)

Prova parziale su uso di Python per l'esplorazione del filesystem.

---

**Lezione 32** (27/2/24)

Comunicazione tra processi mediante named pipe (anche in Python) con riferimento a `pipe(7)`, `fifo(7)`. Comandi `mkfifo(1)` e `mkfifo(3)`. . Lancio di un nuovo eseguibile mediante `fork` seguito da `execl`. Esempio `npipe.c`, `lettore.c` e `lettore.py`.

---

**Lezione 34** (29/2/24)

Introduzione all'uso della memoria condivisa con riferimento a `shm_overview(7)`
Uso e significato di `shm_open`, `ftruncate`, `mmap`, `munmap`, `shm_unlink`.
Esempi uso memoria condivisa. Sorting dello stesso array mendiante due programmi 
distinti (shm_sort2.c e sort3.c).

---

**Lezione 35** (5/3/24)

Problematica di accesso concorrente alla memoria condivisa. 
Introduzione ai semafori con riferimento a `sem_overview(7)`.  Uso e significato di `sem_open`, `sem_post`, `sem_wait`, `sem_unlink`.
Esempio uso semafori per regolare accesso a una variabile condivisa e per segnalare la terminazione di un compito al processo principale (contaprimi_sem.c). Esempio condivisione di semafori tra processi creati con `exec` (sommaprimi.c sommaprimi_aux.c). 

---

**Lezione 36** (7/3/24)

Introduzione ai thread `pthreads(7)`.
Creazione di thread con `pthread_create(3)`
Passaggio di parametri ai thread mediante puntatori a struct
Terminazione e attesa di thread: `pthread_join(3)`
Definizione e utilizzo di mutex.

Nota: potete osservare che il prototipo della funzione `pthread_mutex_init` contiene il modificatore `restrict`. Si tratta di un modificatore riferibile ai puntatori che se usato permette al compilatore di generare del codice più efficiente. Potete trovare ulteriori dettagli ed esempi su [stack overflow](https://stackoverflow.com/questions/745870/realistic-usage-of-the-c99-restrict-keyword).


---

**Lezione 37** (12/3/24)

Introduzione alla tecnica produttori-consumatori.
Sincronizzazione mediante semafori unnamed: `sem_init`, `sem_wait`, `sem_post`, `sem_destroy`.


---

**Lezione 38** (14/3/24)

Tecnica produttori-consumatori con produttori e consumatori multipli. 
Uso di mutex per gestire la concorrenza all'interno dei produttori e/o consumatori.  
Esempio: [esercizioDivisori](./08threads/esercizioDivisori.md)

---

**Lezione 39** (19/3/24)

Introduzione alle Condition Variables.


---


