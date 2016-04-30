#ifndef GAME_SOCKET_H
#define GAME_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <sstream>
#include "errno.h"
#include "logger.hpp"

using namespace std;

#define PEER_DESCONECTADO 0
#define PEER_ERROR -1
#define ESTADO_INICIAL -2

class GameSocket {
protected:
  int socketFd;
  void cerrarSocket();
  void cerrarSocketFd();
  struct sockaddr_in addr_info;
  void iniciarSocket();

public:
    GameSocket();
};
#endif // GAME_SOCKET_H
