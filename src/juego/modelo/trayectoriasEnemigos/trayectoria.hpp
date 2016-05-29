#ifndef INC_1942OLDENAIT_TRAYECTORIA_HPP
#define INC_1942OLDENAIT_TRAYECTORIA_HPP

#include <queue>
#include "tipoMovimiento.hpp"
using namespace std;

class Trayectoria {
protected:
    queue<TipoMovimiento*> colaMovimientos;
public:
    void mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
};


#endif //INC_1942OLDENAIT_TRAYECTORIA_HPP
