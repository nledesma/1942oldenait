#ifndef INC_1942OLDENAIT_GRILLA_HPP
#define INC_1942OLDENAIT_GRILLA_HPP

#include "celda.hpp"
#include "../../juego/modelo/avion.hpp"
#include "../../juego/modelo/disparo.hpp"
#include "../../juego/modelo/avionEnemigo.hpp"
#include <list>
#include "colisionable.hpp"

class Grilla {
private:
    list<list<Celda*>> grilla;
    int cantFilas;
    int cantColumnas;
    float anchoCeldas;
    float altoCeldas;
    list<Celda*> ubicarEnCeldas(Colisionable * colisionable);

public:
    Grilla(int cantFilas, int cantColumnas);
    ~Grilla();
    void ubicarAviones(list<Avion*> aviones);
    void ubicarEnemigos(list<AvionEnemigo*> enemigos);
    void ubicarDisparosAmigos(list<Disparo*> disparos);
    void verificarColisiones();
    void limpiarGrilla();
};

#endif
