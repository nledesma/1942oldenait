#ifndef INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
#define INC_1942OLDENAIT_ESCENARIOJUEGO_HPP

#include <list>
#include <pthread.h>
#include "avion.hpp"
#include "elemento.hpp"
#include "../../accesorios/temporizador.hpp"
#include "../../accesorios/colaConcurrente/colaConcurrente.hpp"
#include <unistd.h>

using namespace std;

class EscenarioJuego {
private:
    list<Avion*> aviones;
    list<Elemento*> elementos;
    list<Disparo*> disparos;
    float velocidadDesplazamientoY;
    Temporizador temporizador;
    float posicionY;
    float scrollingOffset;
    int alto;
    int ancho;
    string idSprite;
    pthread_t mainLoopThread;
    pthread_mutex_t mutexScroll = PTHREAD_MUTEX_INITIALIZER;
    ColaConcurrente<pair<int, int>> colaEventos;
    float posicionNivel;
public:
    void reset();
    EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, string idSprite);
    ~EscenarioJuego();
    float getScrollingOffset();
    void agregarAvion(float posX, float posY, float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos);
    void agregarElemento(float posX, float posY, string idSprite);
    void manejarProximoEvento();
    void manejarEvento(int nroAvion, int evento);
    void actualizarScrollingOffset(float timeStep);
    void pushEvento(pair<int, int> evento);
    void mainLoop();
    static void *mainLoop_th(void* THIS);
    void moverAviones(float timestep);
    void moverElementos(float timestep);
    void moverDisparos(float timeStep);
    list<Avion*>& getAviones();
    list<Elemento*>& getElementos();
    list<Disparo*>& getDisparos();
    int getAncho();
    int getAlto();
    string getIdSprite();
};


#endif //INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
