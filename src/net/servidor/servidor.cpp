#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <list>
#include "servidor.hpp"



using namespace std;

Servidor::Servidor(int port, int cantidadDeClientes):GameSocket(){
	inicializar(port);
}

void Servidor::setCantidadMaximaDeClientes(int unaCantidadDeClientes) {
	cantidadMaximaDeClientes = unaCantidadDeClientes;
}

int Servidor::getCantidadMaximaDeClientes() {
	return cantidadMaximaDeClientes;
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
	listen(this->socketFd, this->cantidadMaximaDeClientes);
}

//Agrega el nuevo cliente a la lista de clientes para aceptarlo.
int Servidor::aceptar(){
	int numeroDeCliente;
	pthread_mutex_lock(&mutexAceptar);
	clientes.push_back(accept(socketFd, 0, 0));
	numeroDeCliente = (clientes.size()-1);
	pthread_mutex_unlock(&mutexAceptar);

	cout << "Conexión aceptada" << endl;

	return numeroDeCliente;

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

void Servidor::setPuerto(int unPuerto) {
	puerto = unPuerto;
}

int Servidor::getPuerto() {
	return puerto;
}
