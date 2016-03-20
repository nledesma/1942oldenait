#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <list>
#include "gameSocket.hpp"
using namespace std;

class Servidor: public GameSocket{
private:
	list <int> clientes;
  struct sockaddr_in addr_info;
public:
	Servidor(int port, int cantidadDeClientes);
	void inicializar(int port);
	void setAddress(int port);
	void pasivar(int backlog);
	void aceptar();
 	void enviarMensaje(string mensaje, int longitudMensaje);
	void cerrar();
};

#endif
