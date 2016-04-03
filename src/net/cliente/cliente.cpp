#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
#include <list>
#include "cliente.hpp"
using namespace std;


Cliente::Cliente(string ip, int port):GameSocket(){
	this->ip = ip;
	this->port = port;
	inicializar(ip,port);
}
void Cliente::inicializar(string serverAddress ,int port){
  this->setAddress(serverAddress, port);
}

void Cliente::agregarMensaje(Mensaje* pMensaje){
  listaMensajes.push_back(pMensaje);
}

void Cliente::setAddress(string serverAddress, int port){
 		this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
  	this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
		this->addr_info.sin_addr.s_addr = inet_addr(serverAddress.c_str()); // Se setea la dirección del server

  	memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

int Cliente::conectar(){
	// Me conecto a la direccion.
	int connected = connect(this->socketFd,(struct sockaddr *) &this->addr_info,sizeof(struct sockaddr_in));
  if (connected == -1){
    cout << "La conexión falló, error" << errno << endl;
		throw runtime_error("CLIENTE_EXCEPTION");
  }
  return connected;
}

void Cliente::cerrar(){
	cerrarSocket();
}

string Cliente::recibir(int longitudMensaje){
	char *mensaje = new char[longitudMensaje];
		int recibidos = 0;
		cout << "Recibiendo el mensaje... " << endl;

		// Le envio los bytes al cliente
	 	while (recibidos < longitudMensaje && recibidos != -1){
  		// Agrego offsets si es que no se envia todo el mensaje
  		recibidos += recv(socketFd, mensaje + recibidos, longitudMensaje - recibidos, 0);
  		if (recibidos == -1){
  			cout << "Error al recibir" << endl;
  		}
  		else{
  		cout << "Recibido " << recibidos << " bytes" << endl;
			}
		}

		mensaje[longitudMensaje - 1] = 0; // Cierro string

		cout << "Recibo el mensaje: " << mensaje << endl;

		return string(mensaje);
}

string Cliente::getIP(){
  return this->ip;
}

int Cliente::getPort(){
  return this->port;
}

list <Mensaje*>& Cliente::getMensajes(){
  return this->listaMensajes;
}

int Cliente::enviarMensajePorId(int idMensaje) {
		Mensaje * mensaje = this->encontrarMensajePorId(idMensaje);
		if((mensaje != NULL)) {
			int msj = GameSocket::enviarMensaje(mensaje, this->socketFd);
			return msj;
		} else {
				Logger::instance()->logInfo("No existe un mensaje con id indicado");
		}
		return -1;
}

//El metodo devuelve el mensaje correspondiente y lo elimina de la coleccion de mensajes
Mensaje * Cliente::encontrarMensajePorId(int idMensaje) {
	bool mensajeEncontrado = false;
	Mensaje * mensaje = NULL;
	list<Mensaje*>::iterator iterador = listaMensajes.begin();
	while(!mensajeEncontrado && (iterador != listaMensajes.end())){
		if ((*iterador)->getId() == idMensaje) {
			mensaje = (*iterador);
			mensajeEncontrado = true;
		}else {
			iterador++;
		}
	}
	return mensaje;
}

void Cliente::ciclarMensajes(int milisegundos) {
	typedef std::chrono::high_resolution_clock Time;
  typedef std::chrono::duration<float> fsec;
	typedef std::chrono::milliseconds ms;
	auto t0 = Time::now();
	auto t1 = Time::now();
	fsec fs = t1 - t0;
	ms d = std::chrono::duration_cast<ms>(fs);
	while(d.count()<milisegundos) {
		list<Mensaje*>::iterator iterador;
		for(iterador = listaMensajes.begin(); iterador != listaMensajes.end(); iterador++) {
				GameSocket::enviarMensaje((*iterador), this->socketFd);
				Mensaje * mensajeRecibido;
				GameSocket::recibirMensaje(mensajeRecibido, this->socketFd);
				cout<< "Id mensaje recibido: " << mensajeRecibido->getId() << endl;
				delete mensajeRecibido;
		}
		t1 = Time::now();
		fs = t1 - t0;
		d = chrono::duration_cast<ms>(fs);
	}
}
