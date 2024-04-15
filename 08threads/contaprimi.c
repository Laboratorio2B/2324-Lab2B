#include "xerrori.h"

// primo esempio di utilizzo di thread
// conteggio dei primi con thread multipli

// mostra come usare una struct per condividere dei parametrei 
// di input e output tra thread principale e ausiliari


//Prototipi
bool primo(int n);

// struct che uso per passare argomenti ai thread
typedef struct {
  int start;            // intervallo dove cercare i primo 
  int end;              // parametri di input
  int somma_parziale;   // parametro di output
} dati;

// funzione passata a pthred_create
void *tbody(void *v) {
  dati *d = (dati *) v;
  int primi = 0;
  // cerco i primi nell'intervallo assegnato
  for(int j=d->start;j<d->end;j++) {
      if(primo(j)) primi++; 
  }
  fprintf(stderr, "Il thread che partiva da %d ha terminato\n", d->start);
  d->somma_parziale = primi;
  pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
  if(argc!=3) {
    fprintf(stderr,"Uso\n\t%s m num_threads\n", argv[0]);
    exit(1);
  }
  // conversione input
  int m= atoi(argv[1]);
  if(m<1) termina("limite primi non valido");
  int p= atoi(argv[2]);
  if(p<=0) termina("numero di thread non valido");

  // creazione thread ausiliari
  pthread_t t[p];   // array di p indentificatori di thread 
  dati d[p];        // array di p struct che passerò ai p thread
  int somma = 0;        // variabile dove accumulo il numero di primi
  for(int i=0; i<p; i++) {
    int n = m/p;  // quanti numeri verifica ogni thread + o - 
    d[i].start = n*i; // inizio range thread i
    d[i].end = (i==p-1) ? m : n*(i+1);
    xpthread_create(&t[i], NULL, &tbody, &d[i],__LINE__, __FILE__); 
  }
  // attendo che i thread abbiano finito
  for(int i=0;i<p;i++) {
    xpthread_join(t[i],NULL,__LINE__, __FILE__);
    somma += d[i].somma_parziale;
  }
  // restituisce il risultato 
  printf("Numero primi tra 1 e %d (escluso): %d\n",m,somma);
  return 0;
}



// restituisce true/false a seconda che n sia primo o composto
bool primo(int n)
{
  if(n<2) return false;
  if(n%2==0) {
    if(n==2)  return true;
    else return false; 
  }
  for (int i=3; i*i<=n; i += 2) 
    if(n%i==0) return false;
  return true;
}

