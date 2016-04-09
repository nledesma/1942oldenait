#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <list>
#include "../mensaje/mensaje.hpp"
#include "../gameSocket.hpp"
#include <queue>
#include <pthread.h>
#include <map>
#include <stdexcept>
#include <errno.h>
#include <cstdlib>
#include <sstream>
#include "../../accesorios/colaConcurrente/colaConcurrente.hpp"
#include "../codigoRespuesta.hpp"

using namespace std;

struct datosCliente {
    pthread_t th_entrada;
    pthread_t th_salida;
    const char *dir;
    ColaConcurrente<Mensaje *> colaSalida;
};

class Servidor : public GameSocket {
private:
    map<int, datosCliente> clientes;
    struct sockaddr_in addr_info;
    ColaConcurrente<pair<int, Mensaje *> > colaDeMensajes;
    pthread_mutex_t mutexAgregar = PTHREAD_MUTEX_INITIALIZER;
    int cantidadMaximaDeClientes;
    int puerto;
    bool servidorActivado;
    pthread_t cicloAceptaciones;
    pthread_t cicloDesencolaciones;
    void desencolarSalidaCliente(int clienteFd);
    int procesarMensaje(Mensaje *mensaje);
    bool validarTipo(int tipo, string valor);
    bool validarInt(string valor);
    bool validarChar(string valor);
    bool validarDouble(string valor);
public:
    bool hayLugar();
    Servidor(int port, int cantidadDeClientes);
    int getCantidadMaximaDeClientes();
    void setCantidadMaximaDeClientes(int unaCantidadDeClientes);
    void inicializar(int port);
    void setAddress(int port);
    void pasivar();
    int aceptar();
    void cerrar();
    int getPuerto();
    void setPuerto(int unPuerto);
    void agregarCliente(int idCliente, pthread_t threadEntrada, pthread_t threadSalida);
    void quitarCliente(int fdCliente);
    static void *atenderCliente(void *arg);
    static void *responderCliente(void *arg);
    static void *cicloAceptar(void *THIS);
    static void *cicloDesencolar(void *THIS);
    void esperar();
    void desactivarServidor();
    bool servidorActivo();
    void encolarMensaje(pair<int, Mensaje *> clienteMensaje);
    void desencolar();
    void revisarClienteConectado(int fdCliente);
    void encolarSalida(int clienteFd, Mensaje *mensaje);
};

#endif
