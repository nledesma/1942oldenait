#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>

using namespace std;

class GameSocket {
protected:
  int socketFd;
  struct sockaddr_in addr_info;

public:
  GameSocket(){
    // Se inicializa el socket para dominios IPv4, tipo de conexión SOCK_STREAM (TCP), y protocolo a definir
    this->socketFd =  socket(PF_INET, SOCK_STREAM, 0);
  }

  


  // TODO Esto no va a ser necesario cuando implementemos un par de funciones más.
  int getSocketFd(){
    return this->socketFd;
  }

};
