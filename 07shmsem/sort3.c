#include "xerrori.h"
#include <time.h>

// programma che esegue il sorting di un oggetto
// di memoria condivisa passato dalla linea
// di comando

// prende come input il nome di un oggetto di
// memoria condivisa, e il numero di interi
// da ordinare

// produce un errore se invocato direttamente
// dalla linea di comando


// funzione di comparazione per qsort
int cmp(const void *a, const void *b)
{
  return *(int*)a - *(int*)b;
}


int main(int argc,char *argv[])
{
  if(argc!=3) {
    fprintf(stderr,"Uso\n\t%s nome_shm num_interi\n", argv[0]);
    exit(1);
  }
  printf("Sto eseguendo: %s %s %s\n",argv[0],argv[1],argv[2]);

  // conversione numero di interi
  int n= atoi(argv[2]);
  if(n<1) termina("dimensione non valida");
  
  // ---- apertura oggetto memoria condivisa
  int shm_size = n*sizeof(int); // un intero x processo
  int fd = xshm_open(argv[1],O_RDWR, 0660,__LINE__,__FILE__);
  int *a = simple_mmap(shm_size,fd, __LINE__,__FILE__);
  close(fd); // dopo mmap e' possibile chiudere il file descriptor

  // ordina gli interi nella memoria condivisa
  qsort(a, n, sizeof(int), cmp);
  
  // unmap memoria condivisa e termina
  xmunmap(a,shm_size,__LINE__, __FILE__);
  return 0;
}
