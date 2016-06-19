#ifndef INC_1942OLDENAIT_TRAYECTORIA_HPP
#define INC_1942OLDENAIT_TRAYECTORIA_HPP

#include <list>
#include "tipoMovimiento.hpp"
using namespace std;

class Trayectoria {
protected:
    list<TipoMovimiento*> movimientos;
    list<TipoMovimiento*>::iterator itMovimientos;
public:
    virtual void mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep) = 0;
    virtual void setEstadoInicial() = 0;
};


#endif //INC_1942OLDENAIT_TRAYECTORIA_HPP
