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
#include "powerUpBonificacion1500.hpp"
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
    int nroEtapaActual;
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
    pthread_mutex_t mutexPowerUps = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexScroll = PTHREAD_MUTEX_INITIALIZER;
    Grilla * grilla;
    //La clave es el numrero del escuadron, el par es de avion que va matando al escuadron y la cantidad de aviones
    //que ya mató, si el numero de avion es -1, significa que varios aviones mataron a los aviones de ese escuadron y
    //la bonificación no corresponde, horrible, ya se.
    map<int, pair<int, int>> infoEscuadrones;
    bool modoPractica;

public:
    void subirPuntaje(int puntos, int nroAvion);
    void reset();
    EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, int anchoVentana, int altoVentana, string idSprite, int modo);
    ~EscenarioJuego();
    void agregarAvion(float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos, int numeroAvion);
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
    bool moverAvionesAposicionFinal(float timeStep);
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
    list<PowerUp*> getPowerUps();
    int getPuntaje(int nroEquipo);
    int getAncho();
    int getAlto();
    int getAnchoVentana();
    int getAltoVentana();
    int getLongitud();
    Etapa * etapaActual();
    list<Etapa *> getEtapas();
    int getNroEtapa();
    string getIdSprite();
    bool estaActivo();
    void activar();
    void desactivar();
    bool porEquipos();
    Avion* avion(int i);
    AvionEnemigo* avionEnemigo(int i);
    void verificarColisiones();
    void proyectarDisparos(float timeStep);
    list<pair<int,int> > getPuntajes();
    void aplicarPowerUp(PowerUp* powerUp, Avion* avion);
    int validarBonificacionEscuadron(AvionEnemigo * avionEnemigo, int nroAvion);
    void iniciarModoPractica();
    void crearPowerUpBonus(float posX, float posY, int valor);

};


#endif
