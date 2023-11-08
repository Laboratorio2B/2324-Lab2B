### Utilizzo di un Raspberry Pi per programmare in assembler ARM


1. Installare sul Raspberry il sistema operativo  [Raspberry Pi OS](https://www.raspberrypi.com/software/): io ho provato anche Ubuntu server ma, oltre ad essere più lento, i programmi non venivano compilati correttamente.


2. Istallare *valgrind* con `sudo apt install valgrind`. Se la versione di *valgrind* è precedente alla 3.17 e segnala errori inesistenti, installate l'ultima versione dal [sito ufficiale](https://valgrind.org/downloads/current.html) seguendo le istruzioni del README.


3. Non ho trovato IDE già configurati per ARM; io utilizzo [Geany](https://geany.org/) (solitamente è già istallato) al quale ho aggiunto qualche configurazione specifica per ARM. In particolare il file *filetypes.asm* contiene la configurazione per l'highlight delle principali parole chiave e per associare ai tasti F8/F9/shift-F9 i comandi Compile/Build/Make. Andando su *Build->Set build commands* potete ridefinire questi comandi (eventualmente per eseguire la cross compilation). Il file *filetypes.asm* va messo nella directory *~/.config/geany/filedefs*. Il file *bespin2.conf* contiene un tema dark ed è da mettere nella directory *~/.config/geany/colorschemes*. Purtroppo non sono riuscito a fargli capire che i commenti iniziano con `@` e non con `;`  per rimediare a questo inizio i commenti con i due caratteri `@;`

4. L'archivio `primi.zip` contiene un esempio di makefile che crea l'eseguibile compilando il file primi.c (che legge l'input e stampa l'output) e il file primo.s che contiene la funzione per verificare se un intero è primo.

