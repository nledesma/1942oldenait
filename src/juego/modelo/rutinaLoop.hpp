#ifndef INC_1942OLDENAIT_RUTINALOOP_HPP
#define INC_1942OLDENAIT_RUTINALOOP_HPP

#include "rutina.hpp"
#include "../../accesorios/trigonomaster.hpp"

class RutinaLoop: public Rutina {
private:
    const float velocidadAngular = 5.625;
public:
    void mover(float &posX, float &posY, float &velocidad, float &angulo, float timestep);
};


#endif //INC_1942OLDENAIT_RUTINALOOP_HPP
