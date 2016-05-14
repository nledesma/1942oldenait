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
#include "decodificador.hpp"
#include "../accesorios/colaConcurrente/colaConcurrente.hpp"

using namespace std;

#define PEER_DESCONECTADO 0 // Si se hace un shutdown, el recv devuelve 0.
#define PEER_ERROR -1 // Si hubo errores, el recv devuelve -1
#define ESTADO_INICIAL -2 // Nuestro, para tener un valor inicial distinto.
#define SIN_CONEXION -3 // Si se intenta recibir algo sin estar conectado.

class GameSocket {
protected:
  int socketFd;
  int enviarBytes(char *pMensaje, int longitudMensaje, int fdReceptor);
  int recibirBytes(string & mensaje, int longitudMensaje, int fdEmisor);
  int enviarMensaje(string mensaje, int fdReceptor);
  int recibirMensaje(string &mensaje, int fdEmisor);
  int setTimeOut(int time);
  void cerrarSocket();
  void cerrarSocketFd();
  struct sockaddr_in addr_info;
  void iniciarSocket();
  bool validarEstadoConexion(int estadoConexion);

public:
    GameSocket();
};
#endif // GAME_SOCKET_H
