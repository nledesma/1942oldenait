#ifndef INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
#define INC_1942OLDENAIT_ESCENARIOJUEGO_HPP

#include <list>
#include <pthread.h>
#include "avion.hpp"
#include "elemento.hpp"
#include "../../accesorios/temporizador.hpp"
#include "../../accesorios/colaConcurrente/colaConcurrente.hpp"

using namespace std;

class EscenarioJuego {
private:
    float offset;
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
    ColaConcurrente<pair<int, char>> colaEventos;
public:
    void reset();
    EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, string idSprite);
    ~EscenarioJuego();
    float getOffset();
    void agregarAvion(float posX, float posY, float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos);
    void agregarElemento(float posX, float posY, string idSprite);
    void manejarProximoEvento();
    void manejarEvento(int nroAvion, char evento);
    void actualizarScrollingOffset(float timeStep);
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
