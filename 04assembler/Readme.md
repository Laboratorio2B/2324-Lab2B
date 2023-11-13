### Utilizzo di un Raspberry Pi per programmare in assembler ARM


1. Installare sul Raspberry il sistema operativo  [Raspberry Pi OS](https://www.raspberrypi.com/software/): ho provato anche Ubuntu server ma, oltre ad essere più lento, i programmi non venivano compilati correttamente. Per l'accesso e lo scambio di file con il Raspberry è necessario utilizzare `ssh` seguendo [questa guida](https://www.raspberrypi.com/documentation/computers/remote-access.html).


2. Installare *valgrind* con `sudo apt install valgrind`. Se la versione di *valgrind* è precedente alla 3.17 e segnala errori inesistenti, installate l'ultima versione dal [sito ufficiale](https://valgrind.org/downloads/current.html) seguendo le istruzioni del README.


3. Non ho trovato IDE già configurati per l'assembler ARM; io utilizzo [Geany](https://geany.org/) (solitamente è già istallato) al quale ho aggiunto qualche configurazione specifica per l'assembler. In particolare il file *filetypes.asm* contiene la configurazione per l'highlight delle principali parole chiave e per associare ai tasti F8/F9/shift-F9 i comandi Compile/Build/Make. Andando su *Build->Set build commands* potete ridefinire questi comandi (eventualmente per eseguire la cross compilation). Il file *filetypes.asm* va messo nella directory *~/.config/geany/filedefs*. Il file *bespin2.conf* contiene un tema dark ed è da mettere nella directory *~/.config/geany/colorschemes*. Purtroppo non sono riuscito a fargli capire che i commenti iniziano con `@` e non con `;`  per rimediare a questo inizio i commenti con i due caratteri `@;`

4. Per testare la compilazione potete usare il file `primi.c` che calcola una tabella di primi utilizzando un test di primalità definito all'interno del file `primo.s`. L'eseguibile viene creato dando il comando `make primi`


5. Se volete utilizzare `gdbgui` come debugger come visto a lezione dovete installarlo con il comando `pip install gdbgui` come descritto sulla [guida ufficiale](https://www.gdbgui.com/).

