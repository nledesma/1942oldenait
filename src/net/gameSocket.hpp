#ifndef GAME_SOCKET_H
#define GAME_SOCKET_H
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
  int enviarBytes(string mensaje, int longitudMensaje, int fdReceptor);
  int recibirBytes(string mensaje, int longitudMensaje, int fdEmisor);
  int enviarMensaje(string mensaje, int fdReceptor);
  int recibirMensaje(string & mensaje, int fdEmisor);
  struct sockaddr_in addr_info;

public:
  GameSocket();
};

#endif // GAME_SOCKET_H
