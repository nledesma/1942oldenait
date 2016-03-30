#ifndef CLIENTE_H
#define CLIENTE_H
#include "../gameSocket.hpp"
#include <list>
#include "../mensaje/mensaje.hpp"
#include <string>
#include <errno.h>
using namespace std;

class Cliente: public GameSocket{
private:
    string ip;
    int port;
    list <Mensaje*> listaMensajes;

public:
	Cliente(string ip, int port);
  void inicializar(string serverAddress ,int port);
  void agregarMensaje(Mensaje* pMensaje);
  void setAddress(string serverAddress, int port);
  int conectar();
  void cerrar();
  string recibir(int longitudMensaje);
  string getIP();
  int getPort();
  list <Mensaje*>& getMensajes();

};
#endif // CLIENTE_H
