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
    void setAddress(string serverAddress, int port);
    int conectar();
    void cerrar();
	/* Lógica del juego */
	void iniciarEscenario();
	void jugar();
	void actualizarEscenario(string mensaje);
	void entreEtapas();
	void cicloMensajes();
	static void * cicloMensajes_th(void* THIS);
	/* Comunicación */
	void esperarJugadores();
	int enviarEvento(int evento);
	void esperarEvento(int evento);
	static void* esperarEvento_th(void* args);
	int recibirMensaje(string & mensaje);
	bool sePuedeEntrar();
    /* getters */
	bool conectado();
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
