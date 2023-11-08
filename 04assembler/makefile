CFLAGS=-std=c11 -g -Wall 
CC=gcc

# eseguibili dei programmi che usano l'assembler 
EXECS=primi


all: $(EXECS)


# costruisce array dei primi <=N
primi: primi.c primo.s
	$(CC) $(CFLAGS) $^ -o primi
	

# regola per cancellare tutti gli  eseguibili e i file oggetto
# serve se voglio rifare tutta la compilazione da capo
# per eseguirla si deve scrivere `make clean` sulla linea di comando 
clean:
	rm -f $(EXECS) *.o
