#ifndef INC_1942OLDENAIT_CELDA_HPP
#define INC_1942OLDENAIT_CELDA_HPP

#include <list>
#include "../../juego/modelo/avion.hpp"
#include "../../juego/modelo/disparo.hpp"
#include "../../juego/modelo/avionEnemigo.hpp"
#include "../../juego/modelo/powerUp.hpp"

class Celda{
private:
    list<Avion*> aviones;
    list<AvionEnemigo*> enemigos;
    list<Disparo*> disparosAmigos;
    list<PowerUp*> powerUps;

public:
    Celda();
    void agregarAvion(Avion * avion);
    void agregarEnemigo(AvionEnemigo * enemigo);
    void agregarDisparoAmigo(Disparo * disparo);
    void agregarPowerUp(PowerUp* powerUp);
    void limpiarCelda();
    void verificarColisiones();
};

#endif
