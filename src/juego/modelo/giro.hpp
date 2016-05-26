#ifndef INC_1942OLDENAIT_GIRO_HPP
#define INC_1942OLDENAIT_GIRO_HPP

#include "../../accesorios/trigonomaster.hpp"

class Giro {
private:
    float transportarAngulo(float &angulo, float velocidadAngular,float timestep);
public:
    void girarAngulo(float &posX, float &posY, float &velocidad, float &angulo, float &anguloAbarrer,
                     int &estadoAnimacion, float velocidadAngular, float timestep);
};


#endif //INC_1942OLDENAIT_GIRO_HPP
