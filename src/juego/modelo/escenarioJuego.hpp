#ifndef INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
#define INC_1942OLDENAIT_ESCENARIOJUEGO_HPP

#include <list>
#include <map>
#include <pthread.h>
#include "avion.hpp"
#include "elemento.hpp"
#include "etapa.hpp"
#include "../../accesorios/temporizador.hpp"
#include "../../accesorios/colaConcurrente/colaConcurrente.hpp"
#include <unistd.h>

using namespace std;

class EscenarioJuego {
private:
    /* Etapas */
    list<Etapa*> etapas;
    list<Etapa*>::iterator itEtapa;
    list<Avion*> aviones;
    list<Elemento*> elementos;
    list<Disparo*> disparos;
    /* Specs */
    float velocidadDesplazamientoY;
    float posicionY;
    float scrollingOffset;
    /* Ventana */
    int anchoVentana;
    int altoVentana;
    /* Fondo */
    int ancho;
    int alto;
    string idSprite;
    /* Estado */
    bool motorActivado;
    /* Sincronización */
    Temporizador temporizador;
    ColaConcurrente<pair<int, int>> colaEventos;
    pthread_t mainLoopThread;
    pthread_mutex_t mutexListaDisparos = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexScroll = PTHREAD_MUTEX_INITIALIZER;

public:
    void reset();
    void siguienteEtapa();
    void comenzarEtapa();
    EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, int anchoVentana, int altoVentana, string idSprite);
    ~EscenarioJuego();
    void agregarAvion(float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos);
    void agregarEtapa(Etapa * etapa);
    /* Eventos */
    void manejarProximoEvento();
    void manejarEvento(int nroAvion, int evento);
    void pushEvento(pair<int, int> evento);
    /* mainLoop */
    void jugar(bool serverActivo);
    static void *mainLoop_th(void* THIS);
    /* Actualizaciones de estado. */
    void actualizarEstado(float timeStep);
    void actualizarScrollingOffset(float timeStep);
    void moverAviones(float timestep);
    void moverElementos(float timestep);
    void moverDisparos(float timeStep);
    /* getters & setters */
    float getScrollingOffset();
    list<Avion*>& getAviones();
    list<Elemento*>& getElementos();
    list<Disparo*> getDisparos();
    int getAncho();
    int getAlto();
    int getAnchoVentana();
    int getAltoVentana();
    int getLongitud();
    Etapa * etapaActual();
    list<Etapa *> getEtapas();
    string getIdSprite();
    bool estaActivo();
    void activar();
    void desactivar();
    Avion* avion(int i);
};


#endif
