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
#include "../../juego/modelo/escenarioJuego.hpp"
#include <chrono>
#include "../decodificador.hpp"

using namespace std;

struct datosCliente {
    pthread_t th_entrada;
    pthread_t th_salida;
    bool conectado;
    ColaConcurrente<string> colaSalida;
    int nroJugador;
    string nombreJugador;
};

class Servidor : public GameSocket {
private:
    map<string, int> nroAvionSegunNombre;
    map<int, datosCliente> clientes;
    map<int , string> direcciones;
    struct sockaddr_in addr_info;
    ColaConcurrente<pair<int, string> > colaDeMensajes;
    pthread_mutex_t mutexAgregar = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexActivarServidor = PTHREAD_MUTEX_INITIALIZER;
    int cantidadMaximaDeClientes;
    int puerto;
    bool servidorActivado;
    pthread_t cicloAceptaciones;
    pthread_t cicloDesencolaciones;
    EscenarioJuego* escenario;
    pthread_mutex_t mutexPartidaLlena = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condPartidaLlena = PTHREAD_COND_INITIALIZER;
    map<string, bool> nombres;
    void desencolarSalidaCliente(int clienteFd);
    bool partidaEnJuego = false;
public:
    map<int, datosCliente> & getClientes();
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
    void agregarCliente(int idCliente, string nombre);
    void quitarCliente(int fdCliente);
    void esperarPartida(int fdCliente);
    void enviarEstadoInicial(int fdCliente);
    static void *atenderCliente(void *arg);
    static void *responderCliente(void *arg);
    static void *cicloAceptar(void *THIS);
    static void *cicloDesencolar(void *THIS);
    void desactivarServidor();
    bool servidorActivo();
    void encolarMensaje(pair<int, string> clienteMensaje);
    void iniciarCicloDesencolaciones();
    void desencolar();
    void encolarSalida(int clienteFd, string mensaje );
    bool clienteConectado(int clienteFd);
    void broadcastEstadoEscenario(string codigoEstadoEscenario);
    EscenarioJuego* getEscenario();
    void setEscenario(EscenarioJuego* unEscenario);
    void imprimirDatosInicialesEscenario();
    void esperarJugadores();
    void signalComienzaPartida();
    string evaluarIngreso(string nombre);
    string obtenerDireccion(int fdCliente);
    void activarPartida();
    bool partidaActiva();
    int clientesFaltantes();
    int nroAvion(string nombre);
};

#endif
