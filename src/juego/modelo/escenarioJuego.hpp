#ifndef INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
#define INC_1942OLDENAIT_ESCENARIOJUEGO_HPP

#include <list>
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
public:
    EscenarioJuego(float velocidadDesplazamientoY);
    ~EscenarioJuego();
    float getOffset();
    void manejarEvento(int nroAvion, char evento);
    void actualizarScrollingOffset(float timeStep);
    static void *mainLoop(void* THIS);
    void moverAviones(float timestep);
    void moverElementos(float timestep);
    void moverDisparos(float timeStep);
    list<Avion*>& getAviones();
    list<Elemento*>& getElementos();
};


#endif //INC_1942OLDENAIT_ESCENARIOJUEGO_HPP
