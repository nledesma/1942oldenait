#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <list>
#include "../mensaje/mensaje.hpp"
#include "../gameSocket.hpp"
#include <queue>
#include <pthread.h>
#include <map>
#include "../../Thread/thread.hpp"
#include "../../Thread/threadAtender.hpp"
#include "../../Thread/threadAceptar.hpp"
using namespace std;

class Thread;

class Servidor: public GameSocket{
private:
	map <int, Thread*> clientes;
  struct sockaddr_in addr_info;
	queue <Mensaje*> colaDeMensajes;
	pthread_mutex_t mutexAgregar = PTHREAD_MUTEX_INITIALIZER;
	int cantidadMaximaDeClientes;
	int puerto;

public:
	Servidor(int port, int cantidadDeClientes);
	int getCantidadMaximaDeClientes();
	void setCantidadMaximaDeClientes(int unaCantidadDeClientes);
	void inicializar(int port);
	void setAddress(int port);
	void pasivar();
	int aceptar();
 	void enviarMensaje(string mensaje, int longitudMensaje);
	void recibirMensaje(string mensaje, int longitudMensaje);
	void cerrar();
	int getPuerto();
	void setPuerto(int unPuerto);
	void* atenderCliente(void* arg);
	void agregarCliente(int idCliente, Thread* thread);
};

#endif
