#include "threadAtender.hpp"

using namespace std;
ThreadAtender::ThreadAtender(Servidor* servidor, int idCliente): Thread(){
  this->servidor = servidor;
  this->idCliente = idCliente;
}

void ThreadAtender::ejecutar(){
    cout << "estoy atendiendo cliente" << endl;

}
