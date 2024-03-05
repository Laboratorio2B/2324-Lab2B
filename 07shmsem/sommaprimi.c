#include "xerrori.h"

// calcola il numero e la somma dei primi contenuti
// alcuni file di testo 
// utilizza dei processi ausiliari per il conteggio
// la comunicazione avviene attraverso 
// shared memory e con il controllo di alcuni semafori 

// il programma ha solo interesse didattico:
// la soluzione implementata è molto inefficiente


#define Sommamem "/sommaprimi"
#define SommasemX "/sommaprimiX"
#define SommasemI "/sommaprimiI"
#define SommasemF "/sommaprimiF"



int main(int argc, char *argv[])
{ 
  if(argc<2) {
    printf("Uso:\n\t%s file1 [file2 file3 ...] \n",argv[0]);
    exit(1);
  }

  // ---- creazione array memoria condivisa
  int shm_size = sizeof(int)+sizeof(long); // uso solo 4+8=12 byte di memoria condivisa (a[0])
  int fd = xshm_open(Sommamem,O_RDWR | O_CREAT, 0660,__LINE__,__FILE__);
  xftruncate(fd, shm_size, __LINE__,__FILE__);
  int *nump = simple_mmap(shm_size,fd, __LINE__,__FILE__);
  long *sommap = (long *) (nump + 1);
  close(fd); // dopo mmap e' possibile chiudere il file descriptor
    
  // ---- creo i semafori
  sem_t *semX = xsem_open(SommasemX,O_CREAT|O_EXCL,0666,1,__LINE__, __FILE__);
  sem_t *semI = xsem_open(SommasemI,O_CREAT|O_EXCL,0666,0,__LINE__, __FILE__);
  sem_t *semF = xsem_open(SommasemF,O_CREAT|O_EXCL,0666,0,__LINE__, __FILE__);
  // inizializzo variabili condivise 
  *nump = 0;
  *sommap = 0;

  // faccio partire i processi ausiliari
  int aux = argc-1;            // numero processi ausiliari
  for(int i=0;i<aux;i++) {
    if(xfork(__LINE__,__FILE__)==0) {
      if(execl("sommaprimi_aux.out", "sommaprimi_aux.out", argv[i+1], (char *) NULL)==-1)
        xtermina("exec fallita",__LINE__,__FILE__);
    }
  }

  // attende inizio dei processi ausiliari
  // quando sono sicuro che i processi ausiliari hanno
  // aperto shm e semafori procedo a prenotare la cancellazione
  // attendo che i figli abbiano fatto sem_post su semI
  for(int i=0;i<aux;i++)
    xsem_wait(semI,__LINE__, __FILE__);
  xshm_unlink(Sommamem,__LINE__, __FILE__);  // distrugge shm quando finito
  xsem_unlink(SommasemX,__LINE__, __FILE__); // distrugge sem quando finito  
  xsem_unlink(SommasemI,__LINE__, __FILE__); // distrugge sem quando finito
  xsem_unlink(SommasemF,__LINE__, __FILE__); // distrugge sem quando finito

  // attendo che i processi figli siano terminati
  // attendo che ogni processo esegua una sem_post(3)
  // su semF per indicare che ha concluso il calcolo 
  for(int i=0;i<aux;i++)
    xsem_wait(semF,__LINE__, __FILE__);


  // ora che tutti i figli hanno terminato posso stampare il risultato
  printf("Numero primi: %d, Somma: %ld\n",*nump,*sommap);
  // chiude i semafori
  xsem_close(semX,__LINE__, __FILE__);
  xsem_close(semI,__LINE__, __FILE__);
  xsem_close(semF,__LINE__, __FILE__);

  fprintf(stderr, "Io %d ho finito.\n",getpid());
  return 0;
}



