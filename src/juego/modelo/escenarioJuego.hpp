#ifndef INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
#define INC_1942OLDENAIT_ESCENARIOJUEGO_HPP

#include <list>
#include <pthread.h>
#include "avion.hpp"
#include "elemento.hpp"
#include "../../accesorios/temporizador.hpp"

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
    pthread_t mainLoopThread;
public:
    void reset();
    EscenarioJuego(float velocidadDesplazamientoY);
    ~EscenarioJuego();
    float getOffset();
    void agregarAvion(Avion * avion);
    void agregarElemento(Elemento * elemento);
    void manejarEvento(int nroAvion, char evento);
    void actualizarScrollingOffset(float timeStep);
    void mainLoop();
    static void *mainLoop_th(void* THIS);
    void moverAviones(float timestep);
    void moverElementos(float timestep);
    void moverDisparos(float timeStep);
    list<Avion*>& getAviones();
    list<Elemento*>& getElementos();
};


#endif //INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
