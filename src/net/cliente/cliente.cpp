#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
#include <list>
#include "cliente.hpp"
using namespace std;

Cliente::Cliente(string ip, int port, Ventana* ventana):GameSocket(){
	this->ip = ip;
	this->port = port;
	this->ventana = ventana;
	cliente_conectado = false;
	setAddress(ip, port);
}

Cliente::Cliente(Ventana* ventana):GameSocket(){
	this->ventana = ventana;
	cliente_conectado = false;
}

Cliente::~Cliente() {}

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
		if (connected == 0) {
			Logger::instance()->logInfo("Conexión exitosa");
			cliente_conectado = true;
			cout << "Conexión exitosa" << endl;
			if (!sePuedeEntrar()) {
				cerrar();
			} else {
				iniciarEscenario();
			}
		} else if (connected == -1) {
			cliente_conectado = false;
			cout << "La conexión falló, error " << errno << endl;
			throw runtime_error("CLIENTE_EXCEPTION");
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
	if(recibirMensaje(mensaje) != MENSAJEOK) return false;
	if (mensaje == "OK"){
		return true;
	} else {
		cout << "No fue posible conectarse. El servidor responde: \"";
		cout << mensaje << "\"" << endl;
		return false;
	}
}

int Cliente::recibirMensaje(string & mensaje){
	if (!cliente_conectado) return SIN_CONEXION;

	int result = this->setTimeOut(3);
	if (result < 0) {
		stringstream ss;
		ss << this->socketFd;
		Logger::instance()->logError(errno,"Se produjo un error al setear el timeOut en el socketfd " + ss.str());
	}

	int estadoRecepcion = GameSocket::recibirMensaje(mensaje, this->socketFd);
	if (estadoRecepcion == PEER_DESCONECTADO) {
		// TODO Convendría mudar esto al cerrado.
		this->cerrarSocketFd();
		cliente_conectado = false;
		if (escenarioVista) escenarioVista->desactivar();
		return estadoRecepcion;
	} else if (estadoRecepcion == PEER_ERROR) {
		this->cerrar();
		return estadoRecepcion;
	} else {
		return MENSAJEOK;
	}
}

int Cliente::enviarEvento(int evento){
	string mensaje = "";
	int estadoEnvio = ESTADO_INICIAL;
	Decodificador::pushEvento(mensaje, evento);
	estadoEnvio = GameSocket::enviarMensaje(mensaje, this->socketFd);
	if (!validarEstadoConexion(estadoEnvio)){
		cout << "Fallo en la conexión al enviar mensaje, se cierra el cliente." << endl;
		this->escenarioVista->desactivar();
		this->cerrar();
	}
	return estadoEnvio;
}

void Cliente::iniciarEscenario(){
	string mensajeRespuesta;
	int n = 10; // Nunca van a ser 10 jugadores, el máximo es 4.
	int n2;

	// Vamos a recibir periódicamente los jugadores que faltan.
	if(recibirMensaje(mensajeRespuesta) != MENSAJEOK) return;
	while(mensajeRespuesta.length() == sizeof(int) && cliente_conectado) {
		n2 = Decodificador::popInt(mensajeRespuesta);
		if (n2 != n){
			n = n2;
			cout << "Faltan " << n2 << " jugadores para comenzar." << endl;
		}
		if(recibirMensaje(mensajeRespuesta) != MENSAJEOK) return;
	}
	// El primer mensaje que no es un entero es el escenario.
	this->escenarioVista = new EscenarioVista(mensajeRespuesta, this->ventana);
	this->escenarioVista->preloop();
	int resultadoRender = CONTINUAR;
	while(escenarioVista->quedanEtapas() && resultadoRender == CONTINUAR) {
		cout << "comienza un ciclo de mensajes." << endl;
		// El ciclo de mensajes termina cuando el escenario sse desactiva.
		this->escenarioVista->activar();
		this->cicloMensajes();
		resultadoRender = this->escenarioVista->comenzarEtapa();
		cout << "terminó una etapa con resultado " << ((resultadoRender==CONTINUAR)?"continuar":"finalizar") << "("<<resultadoRender<<")" << endl;
	}
	if (!escenarioVista->quedanEtapas()) cout << "todas las etapas finalizadas" << endl;
	if (resultadoRender != CONTINUAR) cout << "el resultado de render no fue de continuar" << endl;
	// Terminadas todas las etapas, se cierra el escenario.
	this->escenarioVista->cerrar();
	this->cerrar();
}

void* Cliente::cicloMensajes_th(void * THIS){
	Cliente * cliente = (Cliente *) THIS;
	while(cliente->getEscenario()->getActivo()){
		string mensaje = "";
		int evento = cliente->getEscenario()->popEvento();
		if (evento != EVENTO_VACIO){
			cliente->enviarEvento(evento);
		}
		if(cliente->recibirMensaje(mensaje) != MENSAJEOK) pthread_exit(NULL);

		cliente->actualizarEscenario(mensaje);
	}
	pthread_exit(NULL);
}

void Cliente::cicloMensajes(){
	pthread_create(&mainLoopThread, NULL, cicloMensajes_th, (void*)this);
}

void Cliente::actualizarEscenario(string mensaje){
	if (mensaje.size() == sizeof(int)){
		// Caso evento.
		this->escenarioVista->manejarEvento(Decodificador::popInt(mensaje));
	} else {
		// Caso actualización de estado.
		this->escenarioVista->actualizarComponentes(mensaje);
	}
}

void Cliente::cerrar(){
	if (escenarioVista) escenarioVista->desactivar();
	Logger::instance()->logInfo("Cerrando la conexión del lado del cliente.");
	if (cliente_conectado) {
		cliente_conectado = false;
		cerrarSocket();
	}
}

/* Getters y setters.*/
void Cliente::setAlias(string alias){
	this->alias = alias;
}

string Cliente::getAlias(){
	return this->alias;
}

EscenarioVista * Cliente::getEscenario(){
	return escenarioVista;
}

string Cliente::getIP(){
	return this->ip;
}

int Cliente::getPort(){
	return this->port;
}

bool Cliente::conectado(){
	return cliente_conectado;
}

Ventana* Cliente::getVentana(){
	return this->ventana;
}
