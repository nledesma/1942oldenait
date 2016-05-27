#ifndef INC_1942OLDENAIT_DESPLAZAMIENTO_HPP
#define INC_1942OLDENAIT_DESPLAZAMIENTO_HPP

#include "../../accesorios/trigonomaster.hpp"

class Desplazamiento {
private:
  float cantidadTimesteps;
  float velocidadAngular;
public:
  Desplazamiento(float cantidadTimesteps, float velocidadAngular);
  bool mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
};


#endif //INC_1942OLDENAIT_DESPLAZAMIENTO_HPP
