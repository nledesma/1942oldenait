#ifndef INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
#define INC_1942OLDENAIT_ESCENARIOJUEGO_HPP

#include <list>
#include <map>
#include <set>
#include <pthread.h>
#include "avion.hpp"
#include "avionPequenio.hpp"
#include "avionMediano.hpp"
#include "avionGrande.hpp"
#include "avionDeEscuadron.hpp"
#include "avionEnemigo.hpp"
#include "powerUp.hpp"
#include "powerUpBonificacion.hpp"
#include "powerUpDestruirEnemigos.hpp"
#include "powerUpDosAmetralladoras.hpp"
#include "powerUpAvionesSecundarios.hpp"
#include "trayectoriasEnemigos/trayectoriaCuadrada.hpp"
#include "trayectoriasEnemigos/trayectoriaAvionGrande.hpp"
#include "elemento.hpp"
#include "etapa.hpp"
#include "../../accesorios/temporizador.hpp"
#include "../../accesorios/colaConcurrente/colaConcurrente.hpp"
#include "../../accesorios/colisiones/grilla.hpp"
#include <unistd.h>
#include "../../accesorios/codigo.hpp"

using namespace std;

class EscenarioJuego {
private:
    /* Equipos */
    vector<set<int>> equipos;
    int modoPorEquipos;
    /* Etapas */
    list<Etapa*> etapas;
    list<Etapa*>::iterator itEtapa;
    list<Avion*> aviones;
    list<AvionEnemigo*> enemigos;
    list<Elemento*> elementos;
    list<Disparo*> disparos;
    list<DisparoEnemigo*> disparosEnemigos;
    list<PowerUp*> powerUps;
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
    pthread_mutex_t mutexListaDisparos = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexListaDisparosEnemigos = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexListaEnemigos = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexScroll = PTHREAD_MUTEX_INITIALIZER;
    Grilla * grilla;

public:
    void subirPuntaje(int puntos, int nroAvion);
    void reset();
    EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, int anchoVentana, int altoVentana, string idSprite, int modo);
    ~EscenarioJuego();
    void agregarAvion(float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos);
    void agregarEnemigo(AvionEnemigo* enemigo);
    /* Etapas */
    void agregarEtapa(Etapa * etapa);
    void avanzarEtapa();
    void comenzarEtapa();
    bool quedanEtapas();
    /* Enemigos */
    void getProximoEnemigo();
    /* Eventos */
    void manejarProximoEvento();
    void manejarEvento(int nroAvion, int evento);
    void pushEvento(pair<int, int> evento);
    /* mainLoop */
    void jugar(bool serverActivo);
    void mainLoop();
    /* Actualizaciones de estado. */
    void actualizarEstado(float timeStep);
    void actualizarScrollingOffset(float timeStep);
    void moverAviones(float timestep);
    void moverElementos(float timestep);
    void moverDisparos(float timeStep);
    void moverDisparosEnemigos(float timeStep);
    void moverEnemigos(float timestep);
    void moverPowerUps(float timestep);
    void sortearDisparosEnemigos(float timeStep);
    /* getters & setters */
    float getScrollingOffset();
    list<Avion*>& getAviones();
    list<Elemento*>& getElementos();
    list<Disparo*> getDisparos();
    list<DisparoEnemigo*> getDisparosEnemigos();
    list<AvionEnemigo*> getEnemigos();
    list<PowerUp*> &getPowerUps();
    int getPuntaje(int nroEquipo);
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
    bool porEquipos();
    Avion* avion(int i);
    AvionEnemigo* avionEnemigo(int i);
    void verificarColisiones();
};


#endif
