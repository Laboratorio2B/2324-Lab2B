#include "xerrori.h"
#define QUI __LINE__,__FILE__


// Possibile soluzione al problema lettori/scrittori
// Questa soluzione è unfair per gli scrittori che 
// potrebbero essere messi in attesa indefinita
// se continuano ad arrivare lettori

typedef struct {
  int readers;
  bool writing;
  pthread_cond_t cond;   // condition variable
  pthread_mutex_t mutex; // mutex associato alla condition variable
} rw;


// inizializza rw, ne scrittori ne lettori 
void rw_init(rw *z)
{
  z->readers = 0;
  z->writing = false;
  xpthread_cond_init(&z->cond,NULL,QUI);
  xpthread_mutex_init(&z->mutex,NULL,QUI);
}

// inizio uso da parte di un reader
void read_lock(rw *z)
{
  fprintf(stderr,"%2d read request\n", gettid()%100);
  pthread_mutex_lock(&z->mutex);
  while(z->writing==true)
    pthread_cond_wait(&z->cond, &z->mutex);   // attende fine scrittura
  z->readers++;
  pthread_mutex_unlock(&z->mutex);
}

// fine uso da parte di un reader
void read_unlock(rw *z)
{
  fprintf(stderr,"%2d read completed\n", gettid()%100);
  pthread_mutex_lock(&z->mutex);
  assert(z->readers>0);  // ci deve essere almeno un reader (me stesso)
  assert(!z->writing);   // non ci devono essere writer 
  z->readers--;                  // cambio di stato       
  if(z->readers==0) 
    pthread_cond_signal(&z->cond); // da segnalare ad un solo writer
  pthread_mutex_unlock(&z->mutex);
}
  
// inizio uso da parte di writer  
void write_lock(rw *z)
{
  fprintf(stderr,"%2d write request\n", gettid()%100);
  pthread_mutex_lock(&z->mutex);
  while(z->writing || z->readers>0)
    // attende fine scrittura o lettura
    pthread_cond_wait(&z->cond, &z->mutex);   
  z->writing = true;
  pthread_mutex_unlock(&z->mutex);
}

// fine uso da parte di un writer
void write_unlock(rw *z)
{
  fprintf(stderr,"%2d write completed\n", gettid()%100);
  pthread_mutex_lock(&z->mutex);
  assert(z->writing);
  z->writing=false;               // cambio stato
  // segnala a tutti quelli in attesa 
  pthread_cond_broadcast(&z->cond);  
  pthread_mutex_unlock(&z->mutex);
}


void *lettore(void *arg)
{
  rw *z = (rw *)arg;
  read_lock(z);
  sleep(1);
  read_unlock(z);
  return NULL;
}

void *scrittore(void *arg)
{
  rw *z = (rw *)arg;
  write_lock(z);
  sleep(1);
  write_unlock(z);
  return NULL;
}



int main(int argc, char *argv[])
{
  rw z;
  rw_init(&z);
  // thread che usano la rw
  pthread_t t[20];
  int i=0;
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &scrittore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &scrittore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  xpthread_create(&t[i++],NULL, &lettore, &z, QUI);
  // attendo tutti i thread altrimenti terminano tutti
  for(int j=0; j<i; j++)
    xpthread_join(t[j],NULL,QUI);
  return 0;
}
