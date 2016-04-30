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
        Logger::instance()->logError(errno,"Error al cerrar la conexion.");
    }
}
