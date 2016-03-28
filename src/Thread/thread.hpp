#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <iostream>
using namespace std;

class Thread{
  private:
    pthread_t id;
  protected:
    static void* helper(void* This);
    virtual void ejecutar() = 0;
  public:
    Thread();
    virtual ~Thread();
    bool iniciar();
    void* esperar();
};

#endif
