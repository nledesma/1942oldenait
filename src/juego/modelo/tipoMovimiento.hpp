#ifndef INC_1942OLDENAIT_TIPO_MOVIMIENTO_HPP
#define INC_1942OLDENAIT_TIPO_MOVIMIENTO_HPP

#include "../../accesorios/trigonomaster.hpp"

class TipoMovimiento {
public:
  TipoMovimiento(float parametro1,float parametro2);
  virtual mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
};


#endif //INC_1942OLDENAIT_TIPO_MOVIMIENTO_HPP
