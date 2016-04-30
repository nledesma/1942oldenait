#include "servidor.hpp"

using namespace std;

Servidor::Servidor(int port, int cantidadDeClientes) : GameSocket() {
    try {
        iniciarSocket();
        inicializar(port);
    } catch (runtime_error &e) {
        //Logger::instance()->logError(errno, "Se produjo un error en el BIND");
    }
    setCantidadMaximaDeClientes(cantidadDeClientes);
    iniciarEscenario();
}

void Servidor::setCantidadMaximaDeClientes(int unaCantidadDeClientes) {
    cantidadMaximaDeClientes = unaCantidadDeClientes;
}

int Servidor::getCantidadMaximaDeClientes() {
    return cantidadMaximaDeClientes;
}

void Servidor::inicializar(int port) {
    setPuerto(port);
    this->setAddress(port); // Se setea el puerto en addr_info
    // Se vincula el socket al puerto indicado en addr_info
    if (bind(this->socketFd, (struct sockaddr *) &this->addr_info, sizeof(struct sockaddr_in)) == -1) {
        throw runtime_error("BIND_EXCEPTION");
    }
}

void Servidor::setAddress(int port) {
    this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
    this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
    this->addr_info.sin_addr.s_addr = INADDR_ANY; // El socket se puede asociar a cualquier conexión
    memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

void Servidor::setPuerto(int unPuerto) {
    puerto = unPuerto;
}

int Servidor::getPuerto() {
    return puerto;
}

void Servidor::iniciarEscenario(){
  Escenario* escenario = new Escenario(800, 600);
  this->escenario = escenario;
}

Escenario* Servidor::getEscenario(){
  return this->escenario;
}
