#ifndef COLA_CONCURRENTE_H
#define COLA_CONCURRENTE_H

#include <pthread.h>
#include <queue>
#include "../../net/mensaje/mensaje.hpp"
using namespace std;

template <class T>
class ColaConcurrente {
private:
  queue<T> cola;
  pthread_mutex_t mutexCola = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t mutexDesencolar = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t condDesencolar = PTHREAD_COND_INITIALIZER;
  bool apagar = false;
public:
  ColaConcurrente ();
  virtual ~ColaConcurrente ();
  /* Espera a que haya algo en la cola y quita un elemento*/
  T pop();
  void push(T el);
  bool vacia();
  void avisar();
  int getLong();
};

#endif
