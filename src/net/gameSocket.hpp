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
  struct sockaddr_in addr_info;

public:
  GameSocket();
};
#endif // GAME_SOCKET_H