#include "servidor.hpp"

using namespace std;

Servidor::Servidor(int port, int cantidadDeClientes) : GameSocket() {
    inicializar(port);
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
    bind(this->socketFd, (struct sockaddr *) &this->addr_info,
         sizeof(struct sockaddr_in)); // Se vincula el socket al puerto indicado en addr_info
}

void Servidor::setAddress(int port) {
    this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
    this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
    this->addr_info.sin_addr.s_addr = INADDR_ANY; // El socket se puede asociar a cualquier conexión
    memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
}

void Servidor::pasivar() {
    listen(this->socketFd, this->cantidadMaximaDeClientes);
    servidorActivado = true;
    pthread_create(&this->cicloAceptaciones, NULL, cicloAceptar, (void *) this);
}

void *Servidor::cicloAceptar(void *THIS) {
    Servidor *servidor = (Servidor *) THIS;
    while (servidor->servidorActivo()) {
        int idCliente = servidor->aceptar();
        pthread_t atender;
        pthread_create(&atender, NULL, atenderCliente, NULL);
        servidor->agregarCliente(idCliente, atender);
    }
    pthread_exit(NULL);
}

void *Servidor::atenderCliente(void *arg) {
    cout << "Atendiendo un cliente" << endl;
    pthread_exit(NULL);
}

int Servidor::aceptar() {
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int sockfd_client = accept(socketFd, (sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
    cout << inet_ntoa(client_addr.sin_addr) << endl;
    return sockfd_client;
}

void Servidor::cerrar() {
    this->desactivarServidor();
    pthread_join(this->cicloAceptaciones, NULL);
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

void Servidor::esperar() {
    for (map<int, pthread_t>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++) {
        pthread_join(iterador->second, NULL);
    }
    sleep(2);
}

bool Servidor::servidorActivo() {
    return this->servidorActivado;
}

void Servidor::desactivarServidor() {
    servidorActivado = false;
}

void Servidor::agregarCliente(int idCliente, pthread_t thread) {
    pthread_mutex_lock(&mutexAgregar);
    clientes.insert(pair<int, pthread_t>(idCliente, thread));
    pthread_mutex_unlock(&mutexAgregar);
}
