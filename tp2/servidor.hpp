#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <list>
#include "gameSocket.hpp"
#include "escenario.hpp"
#include <stdexcept>
#include <errno.h>
#include <cstdlib>
#include <sstream>
#include "errno.h"

using namespace std;

class Servidor : public GameSocket {
private:
    struct sockaddr_in addr_info;
    int cantidadMaximaDeClientes;
    int puerto;
    Escenario* escenario;

public:
    Servidor(int port, int cantidadDeClientes);
    int getCantidadMaximaDeClientes();
    void setCantidadMaximaDeClientes(int unaCantidadDeClientes);
    void inicializar(int port);
    void setAddress(int port);
    int getPuerto();
    void setPuerto(int unPuerto);
    void iniciarEscenario(/*int ancho, int alto*/);
    Escenario* getEscenario();
    void setEscenario(Escenario* escenario);
};

#endif
