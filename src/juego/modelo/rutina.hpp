#ifndef INC_1942OLDENAIT_RUTINA_HPP
#define INC_1942OLDENAIT_RUTINA_HPP

#include "../../accesorios/trigonomaster.hpp"

class Rutina {
private:
public:
    virtual void mover(float &posX, float &posY, float &velocidad, float &angulo, float timestep);
};


#endif //INC_1942OLDENAIT_RUTINA_HPP
