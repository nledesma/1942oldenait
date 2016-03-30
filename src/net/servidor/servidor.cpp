#include "servidor.hpp"
using namespace std;

Servidor::Servidor(int port, int cantidadDeClientes):GameSocket(){
	inicializar(port);
	setCantidadMaximaDeClientes(cantidadDeClientes);
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
	pthread_t aceptarID;
	pthread_create(&aceptarID, NULL, cicloAceptar, (void*)this);
}

void * Servidor::cicloAceptar(void * THIS){
	Servidor * servidor = (Servidor*) THIS;
	while(true){
		cout << 1 << endl;
    	int idCliente = servidor->aceptar();
		pthread_t atender;
		pthread_create(&atender, NULL, atenderCliente, NULL);
		servidor->agregarCliente(idCliente, atender);
  }
	pthread_exit(NULL);
}

void * Servidor::atenderCliente(void *arg){
	cout << "Atendiendo un cliente"<< endl;
	pthread_exit(NULL);
}

int Servidor::aceptar(){
  return accept(socketFd, 0, 0);
}

void Servidor::cerrar(){
	for(map<int, pthread_t>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++){
		int clienteActual = (*iterador).first;
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

void Servidor::esperar(){
	for(map<int, pthread_t>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++){
		pthread_join(iterador->second, NULL);
	}
}

void Servidor::agregarCliente(int idCliente, pthread_t thread){
	pthread_mutex_lock(&mutexAgregar);
	clientes.insert(pair<int, pthread_t> (idCliente, thread));
	pthread_mutex_unlock(&mutexAgregar);
}
