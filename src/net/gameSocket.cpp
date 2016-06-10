#include "gameSocket.hpp"

using namespace std;

GameSocket::GameSocket() {
}

void GameSocket::iniciarSocket() {
  // Se inicializa el socket para dominios IPv4, tipo de conexión SOCK_STREAM (TCP), y protocolo a definir
    this->socketFd = socket(PF_INET, SOCK_STREAM, 0);
    int enable = 1;
    if (setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        Logger::instance()->logError(errno, "Socket en uso.");
}

// Dada una cantidad de bytes recibidos, se fija si hubo error en la conexión.
bool GameSocket::validarEstadoConexion(int estadoConexion) {
    return estadoConexion != PEER_DESCONECTADO && estadoConexion != PEER_ERROR;
}

void GameSocket::cerrarSocketFd(){
    close(socketFd);
}

void GameSocket::cerrarSocket() {
    int cerrado = shutdown(socketFd, SHUT_RDWR); // Dejo de transmitir datos

    if(cerrado == 0){
        cout << "Se cerró la conexión." << endl;
        this->cerrarSocketFd();
    } else {
        cout << "Hubo un error al cerrar la conexion (shutdown error)." << endl;
        Logger::instance()->logError(errno,"Error al cerrar la conexion. " + string(strerror(errno)) + ". ");
    }
}

int GameSocket::setTimeOut(int time){
    struct timeval tv;
    tv.tv_sec = time;
    tv.tv_usec = 0;
    return setsockopt(this->socketFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
}

int GameSocket::setSendTimeOut(int time){
    struct timeval tv;
    tv.tv_sec = time;
    tv.tv_usec = 0;
    return setsockopt(this->socketFd, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(struct timeval));
}

int GameSocket::enviarBytes(char *pMensaje, int longitudMensaje, int fdReceptor) {
    int bytesEnviados = 0;
    int bytesActuales = ESTADO_INICIAL;

    while (bytesEnviados < longitudMensaje && validarEstadoConexion(bytesActuales)) {
        // struct timeval tv;
        // tv.tv_sec = 10;
        // tv.tv_usec = 0;
        // setsockopt(fdReceptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(struct timeval));
        int timeOut = 10;
        this->setSendTimeOut(timeOut);
        // Agrego offsets si es que no se envía todo el mensaje
        time_t start = time(0);
        bytesActuales = send(fdReceptor, pMensaje + bytesEnviados, longitudMensaje - bytesEnviados,
                             MSG_NOSIGNAL); // Send retorna la cantidad de byes enviados

        if(bytesActuales < 1) {
            double secondsSinceStart = difftime(time(0), start);
            if(secondsSinceStart >= timeOut){
                return CLIENTE_DESCONECTADO;
            }
        }

        if(bytesActuales == CLIENTE_DESCONECTADO){
            return CLIENTE_DESCONECTADO;
        }

        bytesEnviados += bytesActuales;
    }

    if (bytesActuales == PEER_ERROR) {
        Logger::instance()->logError(errno,"Error al enviar bytes(socket). " + string(strerror(errno)) + ". ");
        return PEER_ERROR;
    } else {
        return MENSAJEOK;
    }
}


int GameSocket::recibirBytes(string & mensaje, int longitudMensaje, int fdEmisor){
    char *pMensaje = new char[longitudMensaje];
    int codigoRet;
    int bytesRecibidos = 0;
    int bytesActuales = ESTADO_INICIAL;

    while (bytesRecibidos < longitudMensaje && validarEstadoConexion(bytesActuales)) {
        // Agrego offsets si es que no se envía todo el mensaje
        bytesActuales = recv(fdEmisor, pMensaje + bytesRecibidos, longitudMensaje - bytesRecibidos,
            0); // Recv retorna la cantidad de bytes recibidos.
        bytesRecibidos += bytesActuales;
    }
    mensaje = string(pMensaje, longitudMensaje);

    if (bytesActuales == PEER_ERROR) {
        Logger::instance()->logError(errno,"Error al recibir bytes (socket). "
            + string(strerror(errno)) + ". ");
        codigoRet = PEER_ERROR;
    } else if (bytesActuales == PEER_DESCONECTADO) {
        Logger::instance()->logInfo("El peer se desconectó.");
        codigoRet = PEER_DESCONECTADO;
    } else {
        codigoRet = MENSAJEOK;
    }
    delete[] pMensaje;

    return codigoRet;
}

int GameSocket::enviarMensaje(string mensaje, int fdReceptor) {
    string longitudMensaje;
    Decodificador::pushCantidad(longitudMensaje, mensaje.size());
    mensaje = longitudMensaje + mensaje;
    // Decodificador::imprimirBytes(mensaje);
    pthread_mutex_lock(&mutexEnviar);
    int resultado = enviarBytes((char *) mensaje.c_str(), mensaje.size(), fdReceptor);
    pthread_mutex_unlock(&mutexEnviar);

    return resultado;
}

int GameSocket::recibirMensaje(string & mensaje, int fdEmisor) {

    string cabecera;
    int resultado = recibirBytes(cabecera, sizeof(int), fdEmisor);

    if (resultado == MENSAJEOK){
        int longMensajeInt = Decodificador::popInt(cabecera);
        if (recibirBytes(mensaje, longMensajeInt, fdEmisor) == MENSAJEOK) {
            // Decodificador::imprimirBytes(mensaje);
            return MENSAJEOK;
        } else {
            stringstream ss;
            ss << "Error al recibir bytes.";
            cout << ss.str() << endl;
            Logger::instance()->logInfo(ss.str());
        }
    } else if (resultado == PEER_DESCONECTADO) {
        return PEER_DESCONECTADO;
    } else {
        Logger::instance()->logInfo("Error al recibir bytes de la cabecera del mensaje.");
    }

    return -1;
}
