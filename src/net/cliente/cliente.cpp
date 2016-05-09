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
	iniciarSocket();
	int conexion;
	try {
		int connected = connect(this->socketFd,(struct sockaddr *) &this->addr_info,sizeof(struct sockaddr_in));
		conexion = connected;
		if(connected == 0) {
			Logger::instance()->logInfo("Conexión exitosa");
			cliente_conectado = true;
			cout << "Conexión exitosa" << endl;
			if (!hayLugar()) {
				cout << "No hay lugar en el servidor" << endl;
				Logger::instance()->logInfo("No hay lugar en el servidor.");
				cerrar();
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

	// Antes de seguir hacemos la etapa inicial.
	iniciarEscenario();

	return conexion;
}

bool Cliente::conectado(){
	return cliente_conectado;
}

void Cliente::cerrar(){
	escenarioVista->cerrar();
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

list <Mensaje*>& Cliente::getMensajes(){
	return this->listaMensajes;
}

int Cliente::enviarMensajePorId(string idMensaje) {
	Mensaje * mensaje = this->encontrarMensajePorId(idMensaje);
	int estadoEnvio = ESTADO_INICIAL;
	if(mensaje != NULL) {
		estadoEnvio = GameSocket::enviarMensaje(mensaje, this->socketFd);
		string info = "Se ha recibido correctamente el mensaje '" + mensaje->getValor()+ "' de tipo " + mensaje->strTipo();
		Logger::instance()->logInfo(info);
		if (!validarEstadoConexion(estadoEnvio)){
			this->cerrar();
		}
	} else {
		estadoEnvio = MENSAJE_INEXISTENTE;
		stringstream ss;
		ss << "No existe un mensaje con el id indicado (" << idMensaje << ")";
		Logger::instance()->logInfo(ss.str());
		cout << ss.str() << endl;
	}
	return estadoEnvio;
}

//El metodo devuelve el mensaje correspondiente y lo elimina de la coleccion de mensajes
Mensaje * Cliente::encontrarMensajePorId(string idMensaje) {
	bool mensajeEncontrado = false;
	Mensaje * mensaje = NULL;
	list<Mensaje*>::iterator iterador = listaMensajes.begin();
	while(!mensajeEncontrado && (iterador != listaMensajes.end())){
		if ((*iterador)->getId() == idMensaje) {
			mensaje = (*iterador);
			mensajeEncontrado = true;
		} else {
			iterador++;
		}
	}
	return mensaje;
}

int Cliente::ciclarMensajes(int milisegundos) {
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;
	typedef std::chrono::milliseconds ms;
	auto t0 = Time::now();
	auto t1 = Time::now();
	fsec fs = t1 - t0;
	int estadoConexion = ESTADO_INICIAL;
	ms d = std::chrono::duration_cast<ms>(fs);
	while(d.count()<milisegundos && validarEstadoConexion(estadoConexion)) {
		list<Mensaje*>::iterator iterador;
		for(iterador = listaMensajes.begin(); iterador != listaMensajes.end(); iterador++) {
			if (validarEstadoConexion(estadoConexion)) {
				estadoConexion = GameSocket::enviarMensaje((*iterador), this->socketFd);
				if (validarEstadoConexion(estadoConexion)) {
					Mensaje *mensajeRecibido;
					estadoConexion = this->recibirMensaje(mensajeRecibido);
					if (estadoConexion == MENSAJEOK) {
						string info = "Id mensaje recibido: "+ mensajeRecibido->getId();
						cout << info << endl;
						Logger::instance()->logInfo(info);
						delete mensajeRecibido;
					}
				}
			}
		}
		t1 = Time::now();
		fs = t1 - t0;
		d = chrono::duration_cast<ms>(fs);
	}
	return estadoConexion;
}

int Cliente::recibirMensaje(Mensaje* &mensaje) {
	int result = this->setTimeOut(3);
	if (result < 0){
		string msj;
		ostringstream msjInfo;
		msjInfo << this->socketFd;
		msj = msjInfo.str();
		Logger::instance()->logError(errno,"Se produjo un error al setear el timeOut en el socketfd " + msj);
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

int Cliente::recibirMensaje(string & mensaje){
	int result = this->setTimeOut(5);
	if (result < 0){
		string msj;
		ostringstream msjInfo;
		msjInfo << this->socketFd;
		msj = msjInfo.str();
		Logger::instance()->logError(errno,"Se produjo un error al setear el timeOut en el socketfd " + msj);
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

bool Cliente::hayLugar(){
	cout << "inicia HAYLUGAR" << endl;
	string mensaje = "";
	GameSocket::recibirMensaje(mensaje, socketFd);
	cout << "fin HAYLUGAR" << endl;
	return (mensaje == "OK");
}

Cliente::~Cliente() {
	while(!this->listaMensajes.empty()) delete this->listaMensajes.front(), this->listaMensajes.pop_front();
}

void Cliente::iniciarEscenario(){
	cout << "iniciando escenario" << endl;
	string mensajeRespuesta;
	do {
		this->recibirMensaje(mensajeRespuesta);
	} while(mensajeRespuesta.length() == sizeof(int));
	// El primer mensaje que no es un entero es el escenario.
	this->escenarioVista = new EscenarioVista(mensajeRespuesta);
	this->escenarioVista->mainLoop();
	this->cicloMensajes();
}

void Cliente::cicloMensajes(){
	while(this->escenarioVista->getActivo()){
		string mensaje = "";
		int evento = this->escenarioVista->popEvento();
		this->enviarEvento(evento);
		this->recibirMensaje(mensaje);
	}
}

int Cliente::enviarEvento(int evento){
	string mensaje = "";
	int estadoEnvio = ESTADO_INICIAL;
	Decodificador::pushEvento(mensaje, evento);
	estadoEnvio = GameSocket::enviarMensaje(mensaje, this->socketFd);
	if(estadoEnvio == MENSAJE_OK){
		Logger::instance()->logInfo("Se ha enviado correctamente el evento");
	}
	if (!validarEstadoConexion(estadoEnvio)){
		this->escenarioVista->setInactivo();
		this->cerrar();
	}
	return estadoEnvio;
}

void Cliente::actualizarComponentes(string mensaje){
	this->escenarioVista->actualizarComponentes(mensaje);
}
