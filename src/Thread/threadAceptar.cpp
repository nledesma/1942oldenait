#include "threadAceptar.hpp"
#include "threadAtender.hpp"
using namespace std;

ThreadAceptar::ThreadAceptar(Servidor* servidor): Thread(){
  this->servidor = servidor;
}

void ThreadAceptar::ejecutar(){
  cout << "EJECUTANDO" << endl;
  while(true){
    cout << 2 << endl;
    int idCliente = servidor->aceptar();
    cout << 3 << endl;
    ThreadAtender* atender = new ThreadAtender(servidor, idCliente);
    cout << 4 << endl;
    servidor->agregarCliente(idCliente, (Thread*)atender);
    cout << "Agrego cliente de id" << idCliente << endl;
    atender->iniciar();
  }
}
