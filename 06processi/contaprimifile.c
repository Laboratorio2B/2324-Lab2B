#include "xerrori.h"

// programma per il conteggio di numero dei primi in un
// intervallo usando piu' processi ausiliari
// e una pipe per comunicare i conteggi parziali 
// al processo genitore


// restituisce true/false a seconda che n sia primo o composto
bool primo(int n)
{
  if(n<2) return false;
  if(n%2==0) {
    if(n==2)  return true;
    else return false; }
  for (int i=3; i*i<=n; i += 2) 
      if(n%i==0) return false;
  return true;
}

// conta quanti sono i primi nel file argv[1]
int main(int argc, char *argv[]) {
  if(argc!=3) {
    printf("Uso:\n\t%s nomefile p\n",argv[0]);
    exit(1);
  }
  FILE *f = fopen(argv[1],"rt");
  if(f==NULL) termina("Non riesco ad aprire il file");
  int p = atoi(argv[2]);
  assert(p>0);
  // creo una pipe di comunicazione dai figli al genitore
  int up[2]; // la chiamo up perchè la uso da figli a genitore
  xpipe(up,__LINE__,__FILE__);
  int down[2];
  xpipe(down,__LINE__,__FILE__);
  for(int i=0;i<p;i++) {
    pid_t pid = xfork(__LINE__,__FILE__);
    if(pid==0) {
      // codice processi figli
      xclose(down[1],__LINE__,__FILE__);
      xclose(up[0],__LINE__,__FILE__);
      int tot = 0;
      while(true) {
        int n;
        int e = read(down[0],&n,sizeof(int));
        if(e==0) break;
        if(e!=sizeof(int)) termina("Errore lettura down");
        if(primo(n)) tot++;
      }
      puts("Figlio ha finito di leggere da down");
      // ho contato quanti primo ho visto
      xclose(down[0],__LINE__,__FILE__);
      int e = write(up[1],&tot,sizeof(tot));
      if(e!=sizeof(tot)) termina("Errore scrittura up");
      xclose(up[1],__LINE__,__FILE__);
      exit(0);
    }    
  }
  // codice genitore
  // chiudo le estermità che non uso
  xclose(down[0],__LINE__,__FILE__);
  xclose(up[1],__LINE__,__FILE__);
  // leggo gli interi e li scrivo in down
  while(true) {
    int x;
    int e = fscanf(f,"%d",&x);
    if(e!=1) break;
    e = write(down[1],&x,sizeof(int));
    if(e!=sizeof(int))
      termina("Errore scrittura pipe down");
  }
  puts("Genitore ha finito di scrivere su down");
  fclose(f);
  // chiudo le estermità che non uso
  xclose(down[1],__LINE__,__FILE__);
  int tot=0;
  // leggo fino a quando tutti non hanno chiuso up[1]
  while(true) {
    int x;
    ssize_t e = read(up[0],&x,sizeof(int));
    if(e==0) break;
    printf("Genitore: letto il valore %d dalla pipe\n",x);
    tot += x;
  }
  xclose(up[0],__LINE__,__FILE__);
  printf("Numero primi nel file %s: %d\n",argv[1],tot);
  return 0;
}
