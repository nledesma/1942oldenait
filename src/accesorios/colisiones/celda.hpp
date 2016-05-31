#include <list>
#include "../../juego/modelo/avion.hpp"
#include "../../juego/modelo/disparo.hpp"
#include "../../juego/modelo/avionEnemigo.hpp"

class Celda{
private:
    list<Avion*> aviones;
    list<AvionEnemigo*> enemigos;
    list<Disparo*> disparosAmigos;

public:
    Celda();
    void agregarAvion(Avion * avion);
    //TODO faltan enemigos, disparos enemigos y powerups
    void agregarEnemigo(AvionEnemigo * enemigo);
    void agregarDisparoAmigo(Disparo * disparo);
    void limpiarCelda();
    void verificarColisiones();
};
