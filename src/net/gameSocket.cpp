#include "gameSocket.hpp"

using namespace std;

GameSocket::GameSocket() {
    // Se inicializa el socket para dominios IPv4, tipo de conexión SOCK_STREAM (TCP), y protocolo a definir
}

void GameSocket::iniciarSocket() {
    this->socketFd = socket(PF_INET, SOCK_STREAM, 0);
}

int GameSocket::enviarBytes(char *pMensaje, int longitudMensaje, int fdReceptor) {
    int bytesEnviados = 0;
    int bytesActuales = 0;

    cout << "Enviando datos" << endl;
    while (bytesEnviados < longitudMensaje && bytesActuales != -1) {
        // Agrego offsets si es que no se envía todo el mensaje
        bytesActuales = send(fdReceptor, pMensaje + bytesEnviados, longitudMensaje - bytesEnviados,
                             MSG_NOSIGNAL); // Send retorna la cantidad de byes enviados
        bytesEnviados += bytesActuales;
        cout << "Enviado " << bytesEnviados << " bytes" << endl;
    }
    cout << "Datos enviados" << endl;
    if (bytesActuales == -1) {
        Logger::instance()->logInfo("Error al enviar bytes(socket).");
        return -1;
    }
    return MENSAJEOK;
}


int GameSocket::recibirBytes(char *pMensaje, int longitudMensaje, int fdEmisor) {

    int bytesRecibidos = 0;
    int bytesActuales = ESTADO_INICIAL;

    while (bytesRecibidos < longitudMensaje && bytesActuales != -1 && bytesActuales != 0) {
        // Agrego offsets si es que no se envía todo el mensaje
        bytesActuales = recv(fdEmisor, pMensaje + bytesRecibidos, longitudMensaje - bytesRecibidos,
                             0); // Recv retorna la cantidad de bytes recibidos.

        bytesRecibidos += bytesActuales;
        cout << "Recibidos " << bytesRecibidos << " bytes:" << endl;
        Mensaje::imprimirBytes(pMensaje, bytesRecibidos);
    }
    if (bytesActuales == -1) {
        Logger::instance()->logInfo("Error al recibir bytes (socket).");
        return -1;
    } else if (bytesActuales == 0) {
        Logger::instance()->logInfo("El peer se desconectó.");
        return PEER_DESCONECTADO;
    } else {
        return MENSAJEOK;
    }
}

void GameSocket::cerrarSocket() {
    int cerrado = shutdown(socketFd, 0); //Dejo de transmitir datos

    if(cerrado == 0){
        cout << "Se cerró la conexión con el servidor" << endl;
        close(socketFd);
    } else {
        cout << "Hubo un error al cerrar la conexion (shutdown error)" << endl;
        Logger::instance()->logError(errno,"Error al cerrar la conexion"); //TODO
    }
}

int GameSocket::enviarMensaje(Mensaje *mensaje, int fdReceptor) {
    const char *pMensaje = mensaje->codificar();
    return enviarBytes((char *) pMensaje, 9 + mensaje->lengthValor() + mensaje->lengthId(), fdReceptor);
}

int GameSocket::recibirMensaje(Mensaje* &mensaje, int fdEmisor) {
    char pInfoMensaje[LONG_INFO_MENSAJE];
    int resultado = recibirBytes(pInfoMensaje, LONG_INFO_MENSAJE, fdEmisor);
    if (resultado == MENSAJEOK) {
        infoMensaje datos = Mensaje::decodificarInfo(pInfoMensaje);
        cout << "ESTO ES EL INFOMENSAJE, tipo" << datos.tipo << endl;
        cout << "ESTO ES EL INFOMENSAJE, longitudId" << datos.longitudId << endl;
        cout << "ESTO ES EL INFOMENSAJE, longitudValor" << datos.longitudValor << endl;


        // TODO ver qué onda las incumbencias.
        char *pMensaje = new char[datos.longitudId + datos.longitudValor];
        if (recibirBytes(pMensaje, datos.longitudId + datos.longitudValor, fdEmisor) == MENSAJEOK) {
            mensaje = new Mensaje(datos, pMensaje);
            delete[] pMensaje;
            return MENSAJEOK;
        } else {
            stringstream ss;
            ss << "Error al recibir bytes del mensaje de tipo" << datos.tipo;
            cout << ss.str() << endl;
            Logger::instance()->logInfo(ss.str());
            delete[] pMensaje;
        }
    } else if (resultado == PEER_DESCONECTADO) {
        return PEER_DESCONECTADO;
    } else {
        Logger::instance()->logInfo("Error al recibir bytes de la cabecera del mensaje.");
    }
    return -1;
}
