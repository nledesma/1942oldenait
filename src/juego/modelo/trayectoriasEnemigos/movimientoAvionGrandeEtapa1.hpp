#ifndef INC_1942OLDENAIT_DESPLAZAMIENTOALTOPE_HPP
#define INC_1942OLDENAIT_DESPLAZAMIENTOALTOPE_HPP

#include "tipoMovimiento.hpp"

class MovimientoAvionGrandeEtapa1 : public TipoMovimiento {
private:
    float yTope;
public:
    MovimientoAvionGrandeEtapa1(float yTope);
    ~MovimientoAvionGrandeEtapa1();
    bool mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
    void setEstadoInicial();
};


#endif //INC_1942OLDENAIT_DESPLAZAMIENTOALTOPE_HPP
