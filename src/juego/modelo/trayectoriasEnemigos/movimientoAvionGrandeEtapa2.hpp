#ifndef INC_1942OLDENAIT_OSCILACIONX_HPP
#define INC_1942OLDENAIT_OSCILACIONX_HPP

#include "tipoMovimiento.hpp"

class MovimientoAvionGrandeEtapa2 : public TipoMovimiento {
private:
    float switchAngulo(float angulo);
public:
    MovimientoAvionGrandeEtapa2();
    ~MovimientoAvionGrandeEtapa2();
    bool mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
};

#endif //INC_1942OLDENAIT_OSCILACIONX_HPP
