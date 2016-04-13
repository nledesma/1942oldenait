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
    desactivarServidor();
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
            if (servidor->hayLugar()){
                Mensaje mensaje(T_STRING, "", "OK");
                servidor->enviarMensaje(&mensaje, fdCliente);
                servidor->agregarCliente(fdCliente);
            } else {
                Mensaje mensaje(T_STRING, "", "NO");
                servidor->enviarMensaje(&mensaje, fdCliente);
            }
        } catch (runtime_error &e) {
            if(servidor->servidorActivo()) {
                Logger::instance()->logError(errno, "Se produjo un error en el ACCEPT");
            }

        }
    }
    pthread_exit(NULL);
}

void *Servidor::atenderCliente(void *arg) {
    pair<Servidor *, int> *parServidorCliente = (pair<Servidor *, int> *) arg;
    Servidor *servidor = parServidorCliente->first;
    int clientfd = parServidorCliente->second;
    int recieveResult = ESTADO_INICIAL;
    // Validar que esté conectado?
    while (recieveResult != PEER_DESCONECTADO && recieveResult != PEER_ERROR && servidor->clienteConectado(clientfd)) {
        Mensaje *mensajeCliente;
        recieveResult = servidor->recibirMensaje(mensajeCliente, clientfd);
        if(recieveResult == MENSAJEOK) {
            pair<int, Mensaje *> clienteMensaje(clientfd, mensajeCliente);
            servidor->encolarMensaje(clienteMensaje);
        } else {
          cout << "Se ha desconectado un cliente" << endl;
        }
    }

    servidor->quitarCliente(clientfd);
    pthread_exit(NULL);
}

// Ciclo que desencola la salida para cada cliente.
void * Servidor::responderCliente(void* arg){
    pair <Servidor *, int> *servidorPar = (pair <Servidor *, int>*) arg;
    Servidor * servidor = servidorPar->first;
    int clienteFd = servidorPar->second;

    while (servidor->servidorActivo() && servidor->clienteConectado(clienteFd)){
        servidor->desencolarSalidaCliente(clienteFd);
    }
    pthread_exit(NULL);
}

bool Servidor::clienteConectado(int clienteFd){
    return clientes[clienteFd].conectado;
}

void Servidor::desencolarSalidaCliente(int clienteFd){
    ColaConcurrente<Mensaje*> *colaSalida = &(clientes[clienteFd].colaSalida);
    Mensaje* mensaje = colaSalida->pop();

    // Por ahí desencola cuando ya cerró el servidor.
    if (!servidorActivado || !clienteConectado(clienteFd)) return;

    int result = procesarMensaje(mensaje);
    if (result == MENSAJE_OK){
      Mensaje * mensajeRespuesta = new Mensaje(T_STRING,mensaje -> getId() + "_OK" ," El mensaje enviado es correcto");
      enviarMensaje(mensajeRespuesta, clienteFd);
      delete mensajeRespuesta;
      delete mensaje;
    } else {
        Mensaje* mensajeError = new Mensaje(T_STRING, mensaje->getId()+"_ERR", "Mensaje erróneo");
        enviarMensaje(mensajeError, clienteFd);
        delete mensajeError;
    }
}

int Servidor::procesarMensaje(Mensaje* mensaje){
    int result;
    string valor = mensaje->getValor();
    int tipo = mensaje->getTipo();
    bool mensajeValido = validarTipo(tipo, valor);
    if (mensajeValido){
        string info = "Se recibió el mensaje con id = "+mensaje->getId()+": '" + valor + "' de tipo " + mensaje->strTipo();
        Logger::instance()->logInfo(info);
        cout << info << endl;
        result = MENSAJE_OK;
    } else {
        string error = "El mensaje recibido con id = "+mensaje->getId()+": '" + valor +"' es inconsistente con el tipo "+ mensaje->strTipo();
        Logger::instance()->logError(INCONSISTENCIA_TIPO_VALOR, error);
        cout << error << endl;
        result = INCONSISTENCIA_TIPO_VALOR;
    }
    return result;

}

int Servidor::aceptar() {

    int resulAccept = accept(socketFd, 0, 0);
    if(this->servidorActivado) {
        Logger::instance()->logInfo("La conexión ha sido aceptada");
    }

    if (resulAccept == -1) {
        throw runtime_error("ACCEPT_EXCEPTION");
    }
    return resulAccept;
}

void Servidor::cerrar() {
    this->desactivarServidor();
    for (map<int, datosCliente>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++) {
        int clienteActual = iterador->first;
        shutdown(clienteActual, 0);
        close(clienteActual);
        iterador->second.colaSalida.avisar();
    }

    cerrarSocket();

    // Cerramos las colas.
    colaDeMensajes.avisar();

    cout << "Servidor cerrado" << endl;
    Logger::instance()->logInfo("El servidor ha sido cerrado");
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
  pthread_mutex_lock(&mutexActivarServidor);
  servidorActivado = false;
  pthread_mutex_unlock(&mutexActivarServidor);

}

void Servidor::encolarMensaje(pair<int, Mensaje *> clienteMensaje) {
    this->colaDeMensajes.push(clienteMensaje);
}

void Servidor::agregarCliente(int fdCliente) {
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    getpeername(fdCliente, (sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
    int port = ntohs(client_addr.sin_port);
    char *clientAddress = inet_ntoa(client_addr.sin_addr);

    stringstream direccionCliente;
    direccionCliente << clientAddress << ":" << port;

    datosCliente datos;
    datos.conectado = true;

    cout << "Conectado a un cliente en la dirección " + direccionCliente.str() << endl;
    Logger::instance()->logInfo("Conectado a un cliente en la dirección " + direccionCliente.str());
    direcciones.insert(pair<int, string>(fdCliente, direccionCliente.str()));

    pthread_mutex_lock(&mutexAgregar);
    clientes.insert(pair<int, datosCliente>(fdCliente, datos));
    pthread_mutex_unlock(&mutexAgregar);

    pair<Servidor *, int> arg(this, fdCliente);

    pthread_create(&(clientes[fdCliente].th_entrada), NULL, atenderCliente, &arg);
    pthread_create(&(clientes[fdCliente].th_salida), NULL, responderCliente, &arg);
}

void Servidor::quitarCliente(int clienteFd) {
    clientes[clienteFd].conectado = false;
    clientes[clienteFd].colaSalida.avisar();
    string msj = "Cliente en la dirección " + direcciones[clienteFd] + " desconectado.";
    cout << msj << endl;
    Logger::instance()->logInfo(msj);
    pthread_join(clientes[clienteFd].th_salida, NULL);
    pthread_join(clientes[clienteFd].th_entrada, NULL);
    this->clientes.erase(clienteFd);
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
    if (!servidorActivado) return;
    encolarSalida(clienteMensaje.first, clienteMensaje.second);
}

bool Servidor::validarChar(string valor) {
    return (valor.length() == 1);
}

bool Servidor::validarInt(string valor) {
    if  (valor.empty() || ((!isdigit(valor[0])) && (valor[0] != '-') && (valor[0] != '+')))
        return false;
    char * p ;
    strtol(valor.c_str(), &p, 10) ;

    return (*p == 0) ;
}

bool Servidor::validarDouble(string valor) {
    if  (valor.empty() || ((!isdigit(valor[0])) && (valor[0] != '-') && (valor[0] != '+')))
        return false;
    char * p ;
    strtod(valor.c_str(), &p) ;

    return (*p == 0) ;
}

bool Servidor::validarTipo(int tipo, string valor) {

    bool esValido;
    switch (tipo) {
        case T_STRING:
            esValido = true;
            break;
        case T_CHAR:
            esValido = validarChar(valor);
            break;
        case T_INT:
            esValido = validarInt(valor);
            break;
        case T_DOUBLE:
            esValido = validarDouble(valor);
            break;
        default:
            esValido = false;
    }
    return esValido;
}

bool Servidor::hayLugar(){
    int clientesActuales;
    pthread_mutex_lock(&mutexAgregar);
    clientesActuales = clientes.size();
    pthread_mutex_unlock(&mutexAgregar);
    return clientesActuales < cantidadMaximaDeClientes;
}
