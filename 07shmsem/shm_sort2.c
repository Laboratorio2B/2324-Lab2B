#include "xerrori.h"
#include <time.h>

// algoritmo di sorting con 2 processi e memoria condivisa
// l'array di input viene messo in una memoria condivisa 
// viene chiamato partition e poi la prima metà è ordinata
// da sort3.out mentre questo processo ordina la seconda metà
// solo dimostrativo: non è un metodo efficiente!!!

// funzione di partizionamento tipo quicksort 
int partition(int a[], int n);


// funzione di comparazione per qsort
int cmp(const void *a, const void *b)
{
  return *(int*)a - *(int*)b;
}


int main(int argc,char *argv[])
{
  if(argc!=3) {
    fprintf(stderr,"Uso\n\t%s dim_array nome_shm\n", argv[0]);
    exit(1);
  }
  // conversione input
  int n= atoi(argv[1]);
  if(n<=1) termina("dimensione non valida");

  // ---- creazione array memoria condivisa
  int shm_size = n*sizeof(int); // un intero x processo
  int fd = xshm_open(argv[2],O_RDWR | O_CREAT, 0660,__LINE__,__FILE__);
  xftruncate(fd, shm_size, __LINE__,__FILE__);
  int *a = simple_mmap(shm_size,fd, __LINE__,__FILE__);
  close(fd); // dopo mmap e' possibile chiudere il file descriptor
  // non effettuo la cancellazione per poter esaminare l'array dalla linea di comando

  // ---- inizializza array condiviso con interi random
  srand(1); // inizializza numeri casuali con lo stesso seed
  for(int i=0; i<n; i++) 
    a[i] = rand()%1000;
  puts("Attendo 2 secondi...");  
  sleep(2);

  puts("riprendo con partition");
  
  // chiamo partition per fare il passo iniziale del quicksort   
  int m = partition(a,n);

  puts("Fine partition. Attendo ancora 2 secondi...");  
  sleep(2);
  
  puts("Ora ordino le due metà separatamente");
  // ---- crea processo figlio  
  pid_t pid= xfork(__LINE__, __FILE__);
  if (pid == 0) {
    // processo figlio lancio programma
    // che ordina la prima metà 
    char b[100];
    sprintf(b,"%d",m);  // scrivo m dentro b[]
    if(execl("sort3.out","sort3.out", argv[2], b, (char *) NULL)==-1)
      xtermina("execl fallita",__LINE__,__FILE__);
    assert(0); // questo codice non dovrebbe essere mai eseguito
  }
  else
  { // processo genitore ordina la seconda metà
    qsort(a+m, n-m, sizeof(int), cmp);
  }
  // aspetta che abbia terminato sort3.out:
  xwait(NULL,__LINE__, __FILE__);
  puts("sort3.out ha terminato");  
    
  // il processo genitore ha ordinato solo la seconda metà
  // la prima è stata ordinata da sort3.out

  // dato che il processo ausiliario è terminato
  // prenoto la cancellazione della shared memory  
  xshm_unlink(argv[2],__LINE__, __FILE__); 


  // qui ci andrebbe eventualmente il codice che usa l'array ordinato
  // mi limito a mettere un controllo
  for(int i=0;i<n-1;i++)
    assert(a[i]<=a[i+1]);

  // unmap memoria condivisa e termina
  xmunmap(a,shm_size,__LINE__, __FILE__);
  return 0;
}



// procedura di partizionamento di un array a[0..n-1]
// partiziona l'array in due parti in modo che gli elementi
// della prima parte sono <= degli elementi della seconda parte
// restituisce il numero di elementi nella prima parte
int partition(int a[], int n)
{
  assert(n>1);
  // scelgo pivot in posizione random 
  int k = random() % n;      // genero posizione random del pivot
  int pivot = a[k];          // elemento pivot
  a[k]=a[0];a[0]=pivot;      // scambia a[k]<->a[0] per mettere il pivot in a[0]

  // procedura di partizionamento
  // l'elemento pivot svolge anche la funzione di sentinella  
  int i= -1;      // puntatore oltre estremo sinistro
  int j = n;      //puntatore oltre estremo destro
  while(1) {
    while(a[--j]>pivot) 
      ; // esce se a[j]<=pivot
    while(a[++i]<pivot) 
      ; // esce se a[i]>=pivot
    if(i<j) {
      // scambia a[i] <-> a[j]
      int t=a[i]; a[i]=a[j]; a[j]=t;
    }
    else break; 
  }
  // la prima meta' e' a[0] .. a[j] quindi ha j+1 elementi   
  assert(j+1 >0);
  assert(j+1 < n);
  printf("Pivot: %d, dimensione prima partizione: %d\n",pivot,j+1);
  return j+1; 
}
