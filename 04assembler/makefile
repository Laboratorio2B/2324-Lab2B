# compilatore e flag per macchine arm7
CFLAGS=-std=c11 -g -Wall 
CC=gcc
# compilatore e flag per cross-compilazione
# CFLAGS=-std=c11 -g -Wall -static 
# CC=arm-linux-gnueabihf-gcc

# eseguibili che si vogliono creare
EXECS=primi strcmp


all: $(EXECS)


# costruisce array dei primi <=N
primi: primi.c primo.s
	$(CC) $(CFLAGS) $^ -o primi
	
# pattern rule valida per tutti gli eseguibili ottenibili
# da un .c e un .s con lo stesso nome ad esempio strcmp.c strcmp.s
# la ricetta per ottenere il target è la stessa in quanto espressa
# in termini delle variabili speciali $ e $@
%: %.c %.s
	$(CC) $(CFLAGS) $^ -o $@


# regola per cancellare tutti gli eseguibili e i file oggetto
# serve se voglio rifare tutta la compilazione da capo
# per eseguirla si deve scrivere `make clean` sulla linea di comando 
clean:
	rm -f $(EXECS) *.o
