#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <list>
#include "gameSocket.hpp"
#include <stack>
using namespace std;

class Servidor: public GameSocket{
private:
	list <int> clientes;
  struct sockaddr_in addr_info;
	stack <Mensaje*> colaDeMensajes;
	pthread_mutex_t mutexAceptar = PTHREAD_MUTEX_INITIALIZER;

public:
	Servidor(int port, int cantidadDeClientes);
	void inicializar(int port);
	void setAddress(int port);
	void pasivar(int backlog);
	int aceptar();
 	void enviarMensaje(string mensaje, int longitudMensaje);
	void recibirMensaje(string mensaje, int longitudMensaje);
	void cerrar();
};

#endif
