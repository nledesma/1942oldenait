#ifndef THREADACEPTAR_H
#define THREADACEPTAR_H
#include "thread.hpp"
#include "../net/servidor/servidor.hpp"
class Servidor;
class ThreadAceptar: public Thread{
  private:
    Servidor* servidor;
  public:
    ThreadAceptar(Servidor* servidor);
    void ejecutar();
};

#endif
