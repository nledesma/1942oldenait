#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <list>
#include "servidor.hpp"
#include "gameSocket.hpp"


using namespace std;

Servidor::Servidor(int port, int cantidadDeClientes):GameSocket(){
	inicializar(port);
}

void Servidor::inicializar(int port){
	this->setAddress(port); // Se setea el puerto en addr_info
	bind(this->socketFd, (struct sockaddr*) &this->addr_info, sizeof(struct sockaddr_in)); // Se vincula el socket al puerto indicado en addr_info
}

void Servidor::setAddress(int port){
	this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
	this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
  this->addr_info.sin_addr.s_addr = INADDR_ANY; // El socket se puede asociar a cualquier conexión
	memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

void Servidor::pasivar(){
	listen(this->socketFd, this->cantidadDeClientes);
}

//Agrega el nuevo cliente a la lista de clientes para aceptarlo.
int Servidor::aceptar(){
	int numeroDecliente;
	pthread_mutex_lock(&mutexAceptar);
	clientes.push_back(accept(socketFd, 0, 0));
	numeroDeCliente = clientes.length())-1;
	pthread_mutex_unlock(&mutexAceptar);

	cout << "Conexión aceptada" << endl;

	return numeroDecliente;

}

void Servidor::enviarMensaje(string mensaje, int longitudMensaje){
	char *pMensaje = &(mensaje[0]);
	int bytesEnviados = 0;

	cout << "Enviando datos" << endl;
	while (bytesEnviados < longitudMensaje && bytesEnviados != -1){
		// Agrego offsets si es que no se envía todo el mensaje
		bytesEnviados += write(clientes.front(), pMensaje + bytesEnviados, longitudMensaje - bytesEnviados);
		cout << "Enviado " << bytesEnviados << " bytes" << endl;
	}
	cout << "Datos enviados" << endl;
}

void Servidor::recibirMensaje(string mensaje, int longitudMensaje){
	char *pMensaje = &(mensaje[0]);
	int bytesRecibidos = 0;

	while (bytesRecibidos < longitudMensaje && bytesRecibidos != -1){
		// Agrego offsets si es que no se envía todo el mensaje
		bytesRecibidos += read(clientes.front(), pMensaje + bytesRecibidos, longitudMensaje - bytesRecibidos);
		cout << "recibidos " << bytesRecibidos << " bytes" << endl;
	}
}

void Servidor::cerrar(){
	for(list<int>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++){
		int clienteActual = *iterador;
			shutdown(clienteActual, 0);
			close(clienteActual);
	}
	shutdown(socketFd, 0); //Dejo de transmitir datos
	close(socketFd);

	cout << "Servidor cerrado" << endl;
}
