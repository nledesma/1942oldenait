#ifndef THREADATENDER_H
#define THREADATENDER_H
#include "thread.hpp"
#include "../net/servidor/servidor.hpp"
class Servidor;

class ThreadAtender: public Thread{
  private:
    Servidor* servidor;
    int idCliente;
  public:
    ThreadAtender(Servidor* servidor, int idCliente);
  protected:
    void ejecutar();
};

#endif
