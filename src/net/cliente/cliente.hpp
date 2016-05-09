#ifndef CLIENTE_H
#define CLIENTE_H
#include "../gameSocket.hpp"
#include "../mensaje/mensaje.hpp"
#include "../decodificador.hpp"
#include "../../juego/vista/escenarioVista.hpp"
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
    list <Mensaje*> listaMensajes;
    bool cliente_conectado;
    Mensaje * encontrarMensajePorId(string idMensaje);
    bool hayLugar();
    EscenarioVista * escenarioVista;
    Decodificador * decodificador;

public:
    Cliente(string ip, int port);
    ~Cliente();
    void inicializar(string serverAddress ,int port);
    void agregarMensaje(Mensaje* pMensaje);
    void setAddress(string serverAddress, int port);
    int conectar();
    bool conectado();
    void cerrar();
    string getIP();
    int getPort();
    int enviarEvento(int evento);
    int enviarMensajePorId(string idMensaje);
    int ciclarMensajes(int milisegundos);
    list <Mensaje*>& getMensajes();
    int recibirMensaje(Mensaje* &mensaje);
    int recibirMensaje(string & mensaje);
    void iniciarEscenario();
    void actualizarComponentes(string mensaje);
};
#endif // CLIENTE_H
