#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
#include <list>
#include "cliente.hpp"
using namespace std;

Cliente::Cliente(string ip, int port, Ventana* ventana):GameSocket() {
	this->ip = ip;
	this->port = port;
	this->ventana = ventana;
	cliente_conectado = false;
	setAddress(ip, port);
}

Cliente::Cliente(Ventana* ventana, SoundBoard* soundBoard):GameSocket() {
	this->ventana = ventana;
	this->soundboard = soundBoard;
	cliente_conectado = false;
}

Cliente::~Cliente() {}

void Cliente::setAddress(string serverAddress, int port){
	this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
	this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
	this->addr_info.sin_addr.s_addr = inet_addr(serverAddress.c_str()); // Se setea la dirección del server

	memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

bool Cliente::conectar(Aviso * aviso){
	// Me conecto a la direccion.
	iniciarSocket();
	try {
		int connected = connect(this->socketFd,(struct sockaddr *) &this->addr_info,sizeof(struct sockaddr_in));
		if (connected == 0) {
			Logger::instance()->logInfo("Conexión exitosa");
			cliente_conectado = true;
			cout << "Conexión exitosa" << endl;
			// Una vez conectado, le preguntamos al servidor si hay lugar.
			if (!sePuedeEntrar(aviso)) {
				// Caso contrario, cerramos la conexión.
				cerrar();
				return false;
			} else {
				return true;
			}
		} else if (connected == -1) {
			cliente_conectado = false;
			if (aviso == NULL) {
				cout << "La conexión falló, error " << errno << endl;
				throw runtime_error("CLIENTE_EXCEPTION");
			} else {
				aviso->avisar("Error en la conexion ("+string(strerror(errno))+")");
			}
			return false;
		}
	} catch(runtime_error &e){
		Logger::instance()->logError(errno,"Se produjo un error en el connect");
	}

	return false;
}

void Cliente::ejecutar() {
	if (cliente_conectado) esperarJugadores();
	if (cliente_conectado) iniciarEscenario();
	if (cliente_conectado) jugar();
	if (cliente_conectado) {
		this->escenarioVista->cerrar();
		this->cerrar();
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

/* Comunicación */

bool Cliente::sePuedeEntrar(Aviso * aviso) {
	// Primero se envía un mensaje con el nombre.
	enviarMensaje(alias, socketFd);
	// Luego el servidor evalua y envia su respuesta. Si es OK se puede.
	string mensaje = "";
	if(recibirMensaje(mensaje) != MENSAJEOK) return false;
	if (mensaje == "OK"){
		cout << "Se puede entrar." << endl;
		return true;
	} else {
		if (aviso == NULL) {
			cout << "No fue posible conectarse. El servidor responde: \"";
			cout << mensaje << "\"" << endl;
		} else {
			cout << "le vamos a avisar al aviso desde el cliente." << endl;
			aviso->avisar("Conexión rechazada: " + mensaje);
		}
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

// Recibe un mensaje los datos para iniciar el escenario y lo hace.
void Cliente::iniciarEscenario() {
	string mensajeInicial;
	if(recibirMensaje(mensajeInicial) != MENSAJEOK) return;
	// TODO si ya había un escenario habría que liberarlo antes de hacer new.
	this->escenarioVista = new EscenarioVista(mensajeInicial, this->ventana, this->soundboard);
	this->escenarioVista->preloop();
}

void Cliente::jugar() {
	// Antes de comenzar nos fijamos si está entre etapas, consultando al servidor.
	string resEntreEtapas;
	recibirMensaje(resEntreEtapas);
	if (Decodificador::popBool(resEntreEtapas)) {
		cout << "El servidor avisa que el cliente se conectó entre etapas." << endl;
		entreEtapas(this->etapas);
	}

	int resultadoRender = CONTINUAR;

	while(escenarioVista->quedanEtapas() && resultadoRender == CONTINUAR && cliente_conectado) {
		cout << "Comienza un ciclo de mensajes." << endl;
		// El ciclo de mensajes termina cuando el escenario sse desactiva.
		this->escenarioVista->activar();
		this->cicloMensajes();
		resultadoRender = this->escenarioVista->comenzarEtapa();

		bool reinicia = false;
		if (this->etapas == -1){
			this->etapas = 0;
			reinicia = true;
		} else {
			this->etapas ++;
		}
		cout << "Terminó una etapa con resultado " << ((resultadoRender==CONTINUAR)?"continuar":"finalizar") << "("<<resultadoRender<<")" << endl;
		if ((resultadoRender == CONTINUAR || resultadoRender == FINALIZADO) && !reinicia) entreEtapas(this->etapas);
		if ((resultadoRender == CONTINUAR || resultadoRender == FINALIZADO) && reinicia) entreEtapas(-1);
	}

	if (!escenarioVista->quedanEtapas()) cout << "Fin del juego." << endl;
	if (resultadoRender != CONTINUAR) cout << "Se procede a salir del juego." << endl;
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
		int evento = Decodificador::popInt(mensaje);
		if (evento == REINICIAR_ESCENARIO)
			this->etapas = -1;
		this->escenarioVista->manejarEvento(evento);
	} else {
		// Caso actualización de estado.
		this->escenarioVista->actualizarComponentes(mensaje);
	}
}

void Cliente::entreEtapas(int nroEtapa) {
	Logger::instance()->logInfo("Entrando al espacio entre etapas");
	string mensaje;
	if (recibirMensaje(mensaje) != MENSAJEOK) {
		this->cerrar();
	} else {
		// Esto se elimina en el hilo creado más abajo, que espera al mensaje del servidor.
		EspacioEntreEtapas e(ventana, mensaje, nroEtapa);

		ArgsEsperarEntreEtapas args;
		args.cliente = this;
		args.espacioEntreEtapas = &e;
		args.evento = FIN_ENTRE_ETAPAS;

		pthread_t esperar_id;
		pthread_create(&esperar_id, NULL, esperarEvento_th, (void*) &args);

		// Render entre etapas.
		if (e.renderLoop() != CONTINUAR) {
			this->cerrar();
		}
		pthread_join(esperar_id, NULL);
	}
	Logger::instance()->logInfo("Saliendo del espacio entre etapas");
}

void Cliente::esperarEvento(int evento) {
	string mensaje = "";
	// TODO ver problemas de conexión.
	int res = MENSAJEOK;
	int eventoRecibido = -1;

	while(res == MENSAJEOK && eventoRecibido != evento) {
		if (mensaje.size() == 4)
			eventoRecibido = Decodificador::popInt(mensaje);
		else
			eventoRecibido = -1;
		res = recibirMensaje(mensaje);
	}
}

// Versión concurrente del método anterior.
void* Cliente::esperarEvento_th(void* argsVoid) {
	ArgsEsperarEntreEtapas * args = (ArgsEsperarEntreEtapas*) argsVoid;
	args->cliente->esperarEvento(args->evento);
	args->espacioEntreEtapas->finalizar();
	pthread_exit(NULL);
}

void Cliente::esperarJugadores() {
	// NOTE estas responsabilidades no le corresponden mucho al cliente, pero no hay tiempo de abstraer más.
	TextoDinamico *texto = new TextoDinamico(25, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
	Figura * fondo = new Figura();
	fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas");

	string mensajeRespuesta;
	int nActual = 10; // Nunca van a ser 10 jugadores, el máximo es 6.
	int nRecibido;
	// TODO ver mecanismo de salida!
	// Vamos a recibir periódicamente los jugadores que faltan.
	if(recibirMensaje(mensajeRespuesta) != MENSAJEOK) return;

	nRecibido = Decodificador::popInt(mensajeRespuesta);
	while(nRecibido != 0 && cliente_conectado) {
		if (nRecibido != nActual) {
			nActual = nRecibido;
			fondo->render(0, 0, ventana->getVentanaRenderer());
			stringstream ss;
			ss << "Falta" << (nRecibido==1?" ":"n ") << nRecibido << (nRecibido==1?" jugador ":" jugadores ") << "para comenzar.";
			texto->cambiarTexto(ss.str());
			texto->renderCentrado(375);
			SDL_RenderPresent(ventana->getVentanaRenderer());
		}
		if(recibirMensaje(mensajeRespuesta) != MENSAJEOK) return;
		nRecibido = Decodificador::popInt(mensajeRespuesta);
	}
	fondo->render(0, 0, ventana->getVentanaRenderer());
	texto->cambiarTexto("Todos los jugadores conectados!");
	texto->renderCentrado(375);
	SDL_RenderPresent(ventana->getVentanaRenderer());
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
