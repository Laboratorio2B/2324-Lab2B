# definizione del compilatore e dei flag di compilazione
# che vengono usate dalle regole implicite
CC=gcc
CFLAGS=-std=c11 -Wall -g -O
LDLIBS=-lm


# su https://www.gnu.org/software/make/manual/make.html#Implicit-Rules
# sono elencate le regole implicite (non tutte) e le variabili 
# usate dalle regole implicite 

# Variabili automatiche: https://www.gnu.org/software/make/manual/make.html#Automatic-Variables
# nei comandi associati ad ogni regola:
#  $@ viene sostituito con il nome del target
#  $< viene sostituito con il primo prerequisito
#  $^ viene sostituito con tutti i prerequisiti

# elenco degli eseguibili da creare
EXECS=legginomi invertifile qsortint qsortstr

# primo target: gli eseguibili sono precondizioni
# quindi verranno tutti creati
all: $(EXECS) 



# regole per la creazione dei file oggetto x listacitta

# versione con il comando di compilazione dato in 
# maniera esplicita (di solito non si fa)
listastringhe.o: listastringhe.c listastringhe.h	
	gcc -std=c11 -Wall -g -c listastringhe.c

legginomi.o: legginomi.c listastringhe.h	
	gcc -std=c11 -Wall -g -c legginomi.c

legginomi: legginomi.o listastringhe.o	
	gcc legginomi.o listastringhe.o -o legginomi


# versione che usa le variabili (molto piu semplice)
invertifile.o: invertifile.c listastringhe.h
	$(CC) $(CFLAGS) -c $<


# regola per la creazione del file eseguibile listacitta
# qui uso $@ per indicare il target (listcitta)
invertifile: invertifile.o listastringhe.o
	$(CC) $^ $(LDLIBS) -o $@


# esempio di target che non corrisponde a una compilazione
# ma esegue la cancellazione dei file oggetto e degli eseguibili
clean: 
	rm *.o $(EXECS)
