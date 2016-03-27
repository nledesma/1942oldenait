#ifndef GAME_SOCKET_H
#define GAME_SOCKET_H
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include "mensaje/mensaje.hpp"

using namespace std;

class GameSocket {
protected:
  int socketFd;
  int enviarBytes(char *pMensaje, int longitudMensaje, int fdReceptor);
  int recibirBytes(char *pMensaje, int longitudMensaje, int fdEmisor);
  virtual int enviarMensaje(Mensaje * mensaje, int fdReceptor);
  virtual int recibirMensaje(Mensaje * mensaje, int fdEmisor);
  struct sockaddr_in addr_info;

public:
  GameSocket();
};

#endif // GAME_SOCKET_H
