#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> //Necesario para el memset
#include <cstdio>
#include <iostream>

using namespace std;

class GameSocket {
private:
  int socketFd;
  struct sockaddr_in addr_info;

public:
  GameSocket(){
    this->socketFd =  socket(PF_INET, SOCK_STREAM, 0); // Se inicializa el socket para dominios IPv4, tipo de conexión SOCK_STREAM (TCP), y protocolo a definir
  }

  void setAddress(int port, char serverAddress[] = NULL){
    this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
    this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red
    if (serverAddress != NULL){ // Si se especifica una dirección de server
      this->addr_info.sin_addr.s_addr = inet_addr(serverAddress); // Se setea la dirección del server
    } else { // De lo contrario
      this->addr_info.sin_addr.s_addr = INADDR_ANY; // El socket se puede asociar a cualquier conexión
    }
    memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
  }

  void inicializarServidor(int port){
    this->setAddress(port); // Se setea el puerto en addr_info
    bind(this->socketFd, (struct sockaddr*) &this->addr_info, sizeof(struct sockaddr_in)); // Se vincula el socket al puerto indicado en addr_info
  }

  void pasivarServidor(int backlog){
    listen(this->socketFd, backlog);
  }

  void inicializarCliente(int port, char serverAddress[] ){
    this->setAddress(port, serverAddress);
  }

  int conectarCliente(){
    int connected = connect(
      this->socketFd,
      (struct sockaddr *) &this->addr_info,
      sizeof(struct sockaddr_in)
    ); //Me conecto a la direccion.
    if (connected != 0){
      cout << "La conexión falló" << endl;
    }
    return connected;
  }

  int getSocketFd(){
    return this->socketFd;
  }

};
