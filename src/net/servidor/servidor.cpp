#include "servidor.hpp"

using namespace std;

Servidor::Servidor(int port, int cantidadDeClientes) : GameSocket() {
    try {
        iniciarSocket();
        inicializar(port);
    } catch (runtime_error &e) {
        Logger::instance()->logError(errno, "Se produjo un error en el BIND");
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

void Servidor::pasivar() {
    int resultadoListen = listen(this->socketFd, this->cantidadMaximaDeClientes);
    cout << "Esperando conexión ... " << endl;
    if (resultadoListen == -1) {
        throw runtime_error("LISTEN_EXCEPTION");
    }
    servidorActivado = true;
    pthread_create(&this->cicloAceptaciones, NULL, cicloAceptar, (void *) this);
    pthread_create(&this->cicloDesencolaciones, NULL, cicloDesencolar, (void *) this );
}

void *Servidor::cicloAceptar(void *THIS) {
    Servidor *servidor = (Servidor *) THIS;
    int fdCliente;
    while (servidor->servidorActivo()) {
        try {
            fdCliente = servidor->aceptar();
            pthread_t atender, responder;
            pair<Servidor *, int> arg(servidor, fdCliente);
            pthread_create(&atender, NULL, atenderCliente, &arg);
            pthread_create(&responder, NULL, responderCliente, &arg);
            servidor->agregarCliente(fdCliente, atender, responder);
        } catch (runtime_error &e) {
            Logger::instance()->logError(errno, "Se produjo un error en el ACCEPT");
        }
    }
    pthread_exit(NULL);
}

void Servidor::revisarClienteConectado(int fdCliente){
    int transmitiendo = recv(fdCliente,NULL,0,0);
    cout << "Resultado de transmitiendo: " << transmitiendo << endl;
}

void *Servidor::atenderCliente(void *arg) {
    pair<Servidor *, int> *parServidorCliente = (pair<Servidor *, int> *) arg;
    Servidor *servidor = parServidorCliente->first;
    int clientfd = parServidorCliente->second;
    cout << "Atendiendo un cliente" << endl;
    int recieveResult = ESTADO_INICIAL;
    while (recieveResult != PEER_DESCONECTADO && recieveResult != PEER_ERROR) {
        Mensaje *mensajeCliente;
        recieveResult = servidor->recibirMensaje(mensajeCliente, clientfd);
        if(recieveResult == MENSAJEOK) {
            string ss = "Se recibió el mensaje '" + mensajeCliente->strValor() + "'.";
            cout << ss << endl;
            Logger::instance()->logInfo(ss);
            pair<int, Mensaje *> clienteMensaje(clientfd, mensajeCliente);
            cout << "Encolando mensaje de id " << clienteMensaje.second->getId() << endl;
            servidor->encolarMensaje(clienteMensaje);
        } else {
          cout << "Error al recibir mensaje." << endl;
        }
    } //TODO : No llega hasta acá (al quitarCliente)... revisar
    servidor->quitarCliente(clientfd);
    pthread_exit(NULL);
}

// Ciclo que desencola la salida para cada cliente.
void * Servidor::responderCliente(void* arg){
    pair <Servidor *, int> *servidorPar = (pair <Servidor *, int>*) arg;
    Servidor * servidor = servidorPar->first;
    int clienteFd = servidorPar->second;

    while (servidor->servidorActivo()){
        servidor->desencolarSalidaCliente(clienteFd);
    }

    pthread_exit(NULL);
}

void Servidor::desencolarSalidaCliente(int clienteFd){
    ColaConcurrente<Mensaje*> *colaSalida = &(clientes[clienteFd].colaSalida);
    Mensaje* mensaje = colaSalida->pop();
    procesarMensaje(mensaje);
}

void Servidor::procesarMensaje(Mensaje* mensaje){
  //TODO TODO TODO URGENTE.
  //HOLA
}

int Servidor::aceptar() {

    int resulAccept = accept(socketFd, 0, 0);
    if (resulAccept == -1) {
        throw runtime_error("ACCEPT_EXCEPTION");
    }
    return resulAccept;
}

void Servidor::cerrar() {
    this->desactivarServidor();
//    pthread_join(this->cicloAceptaciones, NULL);
    for (map<int, datosCliente>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++) {
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
    sleep(10);
    for (map<int, datosCliente>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++) {
        pthread_join(iterador->second.th_entrada, NULL);
        pthread_join(iterador->second.th_salida, NULL);
    }
}

bool Servidor::servidorActivo() {
    return this->servidorActivado;
}

void Servidor::desactivarServidor() {
    servidorActivado = false;
}

void Servidor::encolarMensaje(pair<int, Mensaje *> clienteMensaje) {
    this->colaDeMensajes.push(clienteMensaje);
}

void Servidor::agregarCliente(int fdCliente, pthread_t threadEntrada, pthread_t threadSalida) {
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    getpeername(fdCliente, (sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
    int port = ntohs(client_addr.sin_port); //
    char *clientAddress = inet_ntoa(client_addr.sin_addr);

    stringstream direccionCliente;
    direccionCliente << clientAddress << ":" << port;
    datosCliente datos = {
      .th_entrada = threadEntrada,
      .th_salida = threadSalida,
      .dir = direccionCliente.str().c_str()
    };

    Logger::instance()->logInfo("Conectado a un cliente en la dirección " + direccionCliente.str());

    pthread_mutex_lock(&mutexAgregar);
    clientes.insert(pair<int, datosCliente>(fdCliente, datos));
    pthread_mutex_unlock(&mutexAgregar);
}

void Servidor::quitarCliente(int clientfd) {
    const char *direccionCliente = this->clientes.find(clientfd)->second.dir;
    string tmp(direccionCliente);
    Logger::instance()->logInfo("Cliente en la dirección " + tmp + " desconectado.");
    this->clientes.erase(clientfd);
}

void *Servidor::cicloDesencolar(void *THIS) {
    Servidor *servidor = (Servidor *) THIS;
    while (servidor->servidorActivo()) {
        servidor->desencolar();
    }
    pthread_exit(NULL);
}

void Servidor::encolarSalida(int clienteFd, Mensaje* mensaje){
    clientes[clienteFd].colaSalida.push(mensaje);
}

void Servidor::desencolar() {
    pair<int, Mensaje*> clienteMensaje = colaDeMensajes.pop();
    // Mandar a la variable de salida y darle una señal al thread de salida.
    encolarSalida(clienteMensaje.first, clienteMensaje.second);
    // TODO Esto se borra acá?
    delete clienteMensaje.second;
}
