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
	cliente_conectado = false;
	inicializar(ip, port);
}

void Cliente::inicializar(string serverAddress ,int port){
	this->setAddress(serverAddress, port);
}

void Cliente::setAddress(string serverAddress, int port){
	this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
	this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
	this->addr_info.sin_addr.s_addr = inet_addr(serverAddress.c_str()); // Se setea la dirección del server

	memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

int Cliente::conectar(){
	// Me conecto a la direccion.
	iniciarSocket();
	int conexion;
	try {
		int connected = connect(this->socketFd,(struct sockaddr *) &this->addr_info,sizeof(struct sockaddr_in));
		conexion = connected;
		if(connected == 0) {
			Logger::instance()->logInfo("Conexión exitosa");
			cliente_conectado = true;
			cout << "Conexión exitosa" << endl;
			if (!sePuedeEntrar()) {
				cerrar();
			} else {
				// Antes de seguir hacemos la etapa inicial.
				iniciarEscenario();
			}
		} else {
			if (connected == -1){
				cliente_conectado = false;
				cout << "La conexión falló, error " << errno << endl;
				throw runtime_error("CLIENTE_EXCEPTION");
			}
		}
	} catch(runtime_error &e){
		Logger::instance()->logError(errno,"Se produjo un error en el connect");
	}

	return conexion;
}

bool Cliente::sePuedeEntrar() {
	// Primero se envía un mensaje con el nombre.
	enviarMensaje(alias, socketFd);
	// Luego el servidor evalua y envia su respuesta. Si es OK se puede.
	string mensaje = "";
	GameSocket::recibirMensaje(mensaje, socketFd);
	if (mensaje == "OK"){
		return true;
	} else {
		cout << "No fue posible conectarse. El servidor responde: \"";
		cout << mensaje << "\"" << endl;
		return false;
	}
}

bool Cliente::conectado(){
	return cliente_conectado;
}

void Cliente::cerrar(){
	if (escenarioVista){
		escenarioVista->cerrar();
	}
	Logger::instance()->logInfo("Cerrando la conexión del lado del cliente.");
	cliente_conectado = false;
	cerrarSocket();
}

string Cliente::getIP(){
	return this->ip;
}

int Cliente::getPort(){
	return this->port;
}

int Cliente::recibirMensaje(string & mensaje){
	int result = this->setTimeOut(20);
	if (result < 0){
		stringstream ss;
		ss << this->socketFd;
		Logger::instance()->logError(errno,"Se produjo un error al setear el timeOut en el socketfd " + ss.str());
	}

	int estadoRecepcion = GameSocket::recibirMensaje(mensaje, this->socketFd);
	if (estadoRecepcion == PEER_DESCONECTADO) {
		this->cerrarSocketFd();
		cliente_conectado = false;
		return estadoRecepcion;
	} else if (estadoRecepcion == PEER_ERROR){
		this->cerrar();
		return estadoRecepcion;
	} else {
		return MENSAJEOK;
	}
}

Cliente::~Cliente() {
}

void Cliente::iniciarEscenario(){
	string mensajeRespuesta;
	int n = 10; // Nunca van a ser 10 jugadores, el máximo es 4.
	int n2;

	// Vamos a recibir periódicamente los jugadores que faltan.
	this->recibirMensaje(mensajeRespuesta);
	while(mensajeRespuesta.length() == sizeof(int)){
		n2 = Decodificador::popInt(mensajeRespuesta);
		if (n2 != n){
			n = n2;
			cout << "Faltan " << n2 << " jugadores para comenzar." << endl;
		}
		this->recibirMensaje(mensajeRespuesta);
	}
	// El primer mensaje que no es un entero es el escenario.
	this->escenarioVista = new EscenarioVista(mensajeRespuesta);
	this->escenarioVista->setActivo();
	this->escenarioVista->preloop();
	this->cicloMensajes();
	this->escenarioVista->mainLoop();
	this->cerrar();
}

void* Cliente::cicloMensajes_th(void * THIS){
	Cliente * cliente = (Cliente *) THIS;
	cout << "Comienza el ciclo de mensajes del cliente." << endl;
	while(cliente->getEscenario()->getActivo()){
		string mensaje = "";
		int evento = cliente->getEscenario()->popEvento();
		if (evento != EVENTO_VACIO){
			cliente->enviarEvento(evento);
					}
		// cout << "Se envía el evento " << evento << endl;
		// cout << "Se efectua una lectura..." << endl;
		cliente->recibirMensaje(mensaje);
		// cout << "Se recibió el mensaje: " << endl;
		// Decodificador::imprimirBytes(mensaje);
		cliente->actualizarComponentes(mensaje);
	}
	pthread_exit(NULL);
}

void Cliente::cicloMensajes(){
	pthread_create(&mainLoopThread, NULL, cicloMensajes_th, (void*)this);
}

int Cliente::enviarEvento(int evento){
	string mensaje = "";
	int estadoEnvio = ESTADO_INICIAL;
	Decodificador::pushEvento(mensaje, evento);
	estadoEnvio = GameSocket::enviarMensaje(mensaje, this->socketFd);
	if (!validarEstadoConexion(estadoEnvio)){
		cout << "Fallo en la conexión, se cierra el cliente." << endl;
		this->escenarioVista->setInactivo();
		this->cerrar();
	}
	return estadoEnvio;
}

void Cliente::actualizarComponentes(string mensaje){
	this->escenarioVista->actualizarComponentes(mensaje);
}

void Cliente::setAlias(string alias){
	this->alias = alias;
}

string Cliente::getAlias(){
	return this->alias;
}

EscenarioVista * Cliente::getEscenario(){
	return escenarioVista;
}
