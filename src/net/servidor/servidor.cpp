#include "servidor.hpp"

using namespace std;

Servidor::Servidor(int port, int cantidadDeClientes) : GameSocket() {
	try{
		inicializar(port);
	}catch(runtime_error &e){
		Logger::instance()->logError(errno,"Se produjo un error en el BIND");
	}
    setCantidadMaximaDeClientes(cantidadDeClientes);
    servidorActivado = false;
}

void Servidor::setCantidadMaximaDeClientes(int unaCantidadDeClientes) {
    cantidadMaximaDeClientes = unaCantidadDeClientes;
}

int Servidor::getCantidadMaximaDeClientes() {
    return cantidadMaximaDeClientes;
}

void Servidor::inicializar(int port) {
    this->setAddress(port); // Se setea el puerto en addr_info
	// Se vincula el socket al puerto indicado en addr_info
	if(bind(this->socketFd, (struct sockaddr*) &this->addr_info, sizeof(struct sockaddr_in)) == -1){
		throw runtime_error("BIND_EXCEPTION");
	 }
}

void Servidor::setAddress(int port) {
    this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
    this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
    this->addr_info.sin_addr.s_addr = INADDR_ANY; // El socket se puede asociar a cualquier conexión
    memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

void Servidor::pasivar() {
	if(listen(this->socketFd, this->cantidadMaximaDeClientes) == -1){
		throw runtime_error("LISTEN_EXCEPTION");
	}
    servidorActivado = true;
    pthread_create(&this->cicloAceptaciones, NULL, cicloAceptar, (void *) this);
}

void *Servidor::cicloAceptar(void *THIS) {
    Servidor *servidor = (Servidor *) THIS;
	int fdCliente;
    while (servidor->servidorActivo()) {
		try{
    	fdCliente = servidor->aceptar();
			pthread_t atender;
			pthread_create(&atender, NULL, atenderCliente, NULL);
			servidor->agregarCliente(fdCliente, atender);
	  }
		catch(runtime_error &e){
			Logger::instance()->logError(errno,"Se produjo un error en el ACCEPT");
			cout << "La conexión falló, por favor intente nuevamente conectarse" << endl;
			//TODO llamar mainMenu()
		}
	}
    pthread_exit(NULL);
}

void *Servidor::atenderCliente(void *arg) {
    cout << "Atendiendo un cliente" << endl;
    pthread_exit(NULL);
}

int Servidor::aceptar() {

	int resulAccept = accept(socketFd,0,0);
	if(resulAccept == -1){
		throw runtime_error("ACCEPT_EXCEPTION");
	}
	return resulAccept;
}

void Servidor::cerrar() {
    this->desactivarServidor();
//    pthread_join(this->cicloAceptaciones, NULL);
    for (map<int, pthread_t>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++) {
        int clienteActual = (*iterador).first;
        shutdown(clienteActual, 0);
        close(clienteActual);
    }

    cerrarSocket();

    cout << "Servidor cerrado" << endl;
}

void Servidor::setPuerto(int unPuerto) {
    puerto = unPuerto;
}

int Servidor::getPuerto() {
    return puerto;
}

void Servidor::esperar(){
	sleep(10);
	for(map<int, pthread_t>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++){
		pthread_join(iterador->second, NULL);
	}
}

bool Servidor::servidorActivo() {
    return this->servidorActivado;
}

void Servidor::desactivarServidor() {
    servidorActivado = false;
}

void Servidor::agregarCliente(int fdCliente, pthread_t thread) {
	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);
	getpeername(fdCliente, (sockaddr*) &client_addr, (socklen_t*) &client_addr_len);
	int port = ntohs(client_addr.sin_port); //
	char* clientAddress = inet_ntoa(client_addr.sin_addr);

	stringstream ss;
	ss << "Conectado a un cliente en el puerto: " << clientAddress << ":" << port;
	const std::string tmp = ss.str();
	const char* cstr = tmp.c_str();

	Logger::instance()->logInfo(cstr);

//	clientAddress = strcat(clientAddress, &portSeparador);
//	clientAddress = strcat(clientAddress, pchar);
//	cout << clientAddress << endl;
	pthread_mutex_lock(&mutexAgregar);
    clientes.insert(pair<int, pthread_t>(fdCliente, thread));
    pthread_mutex_unlock(&mutexAgregar);
}
