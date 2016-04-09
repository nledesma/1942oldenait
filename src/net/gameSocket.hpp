#ifndef GAME_SOCKET_H
#define GAME_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <sstream>
#include "mensaje/mensaje.hpp"
#include "../logger/logger.hpp"
#include "../accesorios/colaConcurrente/colaConcurrente.hpp"

using namespace std;

#define PEER_DESCONECTADO 0
#define PEER_ERROR -1
#define ESTADO_INICIAL -2

class GameSocket {
protected:
  int socketFd;
  int enviarBytes(char *pMensaje, int longitudMensaje, int fdReceptor);
  int recibirBytes(char *pMensaje, int longitudMensaje, int fdEmisor);
  int enviarMensaje(Mensaje * mensaje, int fdReceptor);
  int recibirMensaje(Mensaje *&mensaje, int fdEmisor);
  void cerrarSocket();
  void cerrarSocketFd();
  struct sockaddr_in addr_info;
  void iniciarSocket();
  bool validarEstadoConexion(int estadoConexion);

public:
    GameSocket();
};
#endif // GAME_SOCKET_H
