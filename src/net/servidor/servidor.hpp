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
#include <stdexcept>
#include <errno.h>
#include <cstdlib>
#include <sstream>

// #include "../../Thread/thread.hpp"
// #include "../../Thread/threadAtender.hpp"
// #include "../../Thread/threadAceptar.hpp"
using namespace std;
// class Thread;

struct datosCliente{
	pthread_t th;
	const char* dir;
};

class Servidor: public GameSocket{
private:
	map <int, datosCliente> clientes;
  	struct sockaddr_in addr_info;
	queue < pair<int, Mensaje*> > colaDeMensajes;
	pthread_mutex_t mutexAgregar = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t mutexCola = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t mutexDesencolar = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t condDesencolar = PTHREAD_COND_INITIALIZER;
	int cantidadMaximaDeClientes;
	int puerto;
	bool servidorActivado;
	pthread_t cicloAceptaciones;
	pthread_t cicloDesencolaciones;

public:
	Servidor(int port, int cantidadDeClientes);
	int getCantidadMaximaDeClientes();
	void setCantidadMaximaDeClientes(int unaCantidadDeClientes);
	void inicializar(int port);
	void setAddress(int port);
	void pasivar();
	int aceptar();
	void cerrar();
	int getPuerto();
	void setPuerto(int unPuerto);
	void agregarCliente(int idCliente, pthread_t thread);
	void quitarCliente(int fdCliente);
	static void *atenderCliente(void* THIS);
	static void *cicloAceptar(void* THIS);
	static void *cicloDesencolar(void* THIS);
	void esperar();
	void desactivarServidor();
	bool servidorActivo();
	void encolarMensaje(pair <int, Mensaje*> clienteMensaje);
	void desencolar();
	void revisarClienteConectado(int fdCliente);
};

#endif
