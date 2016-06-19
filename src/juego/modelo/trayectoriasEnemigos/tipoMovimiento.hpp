#ifndef INC_1942OLDENAIT_TIPO_MOVIMIENTO_HPP
#define INC_1942OLDENAIT_TIPO_MOVIMIENTO_HPP

#include "../../../accesorios/trigonomaster.hpp"

class TipoMovimiento {
public:
  virtual bool mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep) = 0;
    virtual void setEstadoInicial() = 0;
};


#endif //INC_1942OLDENAIT_TIPO_MOVIMIENTO_HPP
