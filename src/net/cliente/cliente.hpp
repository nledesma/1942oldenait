#ifndef CLIENTE_H
#define CLIENTE_H
#include "../gameSocket.hpp"
#include "../mensaje/mensaje.hpp"
#include "../decodificador.hpp"
#include "../../juego/vista/escenarioVista.hpp"
#include "../codigoRespuesta.hpp"
#include <list>
#include <string>
#include <errno.h>
#include <stdexcept>
#include <queue>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <chrono>
#include <sstream>

using namespace std;
#define MENSAJE_INEXISTENTE -2

class Cliente: public GameSocket{
private:
    string ip;
    int port;
    bool cliente_conectado;
    EscenarioVista * escenarioVista = NULL;
    string alias;
    pthread_t mainLoopThread;

public:
    Cliente(string ip, int port);
    ~Cliente();
    void inicializar(string serverAddress ,int port);
    void setAddress(string serverAddress, int port);
    int conectar();
    bool conectado();
    void cerrar();
    int enviarEvento(int evento);
    int recibirMensaje(string & mensaje);
    void iniciarEscenario();
    void actualizarComponentes(string mensaje);
    void cicloMensajes();
    static void * cicloMensajes_th(void* THIS);
    bool sePuedeEntrar();
    /* getters */
    EscenarioVista * getEscenario();
    string getIP();
    int getPort();
    string getAlias();
    void setAlias(string alias);
};
#endif // CLIENTE_H
