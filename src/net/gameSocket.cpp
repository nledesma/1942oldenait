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

int GameSocket::setTimeOut(int time){
    struct timeval tv;
    tv.tv_sec = time;
    tv.tv_usec = 0;
    return setsockopt(this->socketFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
}

int GameSocket::enviarBytes(char *pMensaje, int longitudMensaje, int fdReceptor) {
    int bytesEnviados = 0;
    int bytesActuales = ESTADO_INICIAL;

    while (bytesEnviados < longitudMensaje && validarEstadoConexion(bytesActuales)) {
        // Agrego offsets si es que no se envía todo el mensaje
        bytesActuales = send(fdReceptor, pMensaje + bytesEnviados, longitudMensaje - bytesEnviados,
                             MSG_NOSIGNAL); // Send retorna la cantidad de byes enviados
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

void GameSocket::cerrarSocketFd(){
    close(socketFd);

}

void GameSocket::cerrarSocket() {
    int cerrado = shutdown(socketFd, 0); //Dejo de transmitir datos

    if(cerrado == 0){
        cout << "Se cerró la conexión." << endl;
        this->cerrarSocketFd();
    } else {
        cout << "Hubo un error al cerrar la conexion (shutdown error)." << endl;
        Logger::instance()->logError(errno,"Error al cerrar la conexion. " + string(strerror(errno)) + ". ");
    }
}

int GameSocket::enviarMensaje(string mensaje, int fdReceptor) {
    cout << "Enviando mensaje: ";
    Decodificador::imprimirBytes(mensaje);
    string longitudMensaje;
    Decodificador::pushCantidad(longitudMensaje, mensaje.size());
    mensaje = longitudMensaje + mensaje;
    return enviarBytes((char *) mensaje.c_str(), mensaje.size(), fdReceptor);
}

//TODO probar!!!!
int GameSocket::recibirMensaje(string & mensaje, int fdEmisor){
    string cabecera;
    int resultado = recibirBytes(cabecera, sizeof(int), fdEmisor);
    cout << "Se recibió la cabecera: " << endl;
    Decodificador::imprimirBytes(cabecera);

    if (resultado == MENSAJEOK){
        int longMensajeInt = Decodificador::popInt(cabecera);
        if (recibirBytes(mensaje, longMensajeInt, fdEmisor) == MENSAJEOK) {
            cout << "Se recibió el mensaje: " << endl;
            Decodificador::imprimirBytes(mensaje);
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


bool GameSocket::validarEstadoConexion(int estadoConexion) {
    if (estadoConexion != PEER_DESCONECTADO && estadoConexion != PEER_ERROR)
        return true;
    return false;
}
