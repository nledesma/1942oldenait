#ifndef CLIENTE_H
#define CLIENTE_H
#include "../gameSocket.hpp"
#include "../decodificador.hpp"
#include "../../juego/vista/escenarioVista.hpp"
#include "../../juego/vista/espacioEntreEtapas.hpp"
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

struct Conexion {
	string nombre;
	string ip;
	int puerto;
};

using namespace std;

class Cliente: public GameSocket{
private:
    string ip;
    int port;
    bool cliente_conectado;
    EscenarioVista * escenarioVista = NULL;
    string alias;
    pthread_t mainLoopThread;
	Ventana* ventana;

public:
    Cliente(string ip, int port, Ventana* ventana);
	Cliente(Ventana* ventana);
    ~Cliente();
    void inicializar(string serverAddress ,int port);
    void setAddress(string serverAddress, int port);
    int conectar();
    bool conectado();
    void cerrar();
    int enviarEvento(int evento);
	void esperarEvento(int evento);
	static void* esperarEvento_th(void* args);
    int recibirMensaje(string & mensaje);
    void iniciarEscenario();
    void actualizarEscenario(string mensaje);
    void cicloMensajes();
    static void * cicloMensajes_th(void* THIS);
    bool sePuedeEntrar();
	void entreEtapas();
    /* getters */
    EscenarioVista * getEscenario();
    string getIP();
    int getPort();
    string getAlias();
    void setAlias(string alias);
	Ventana* getVentana();
};

struct ArgsEsperarEntreEtapas {
	Cliente * cliente;
	EspacioEntreEtapas * espacioEntreEtapas;
	int evento;
};

#endif // CLIENTE_H
