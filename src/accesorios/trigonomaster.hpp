#ifndef INC_1942OLDENAIT_TRIGONOMASTER_HPP
#define INC_1942OLDENAIT_TRIGONOMASTER_HPP

#include <math.h>

#define PORCION_ANGULO 0.044444444

class Trigonomaster {
private:
public:
    static float getSeno(float angulo, int &anguloAnimacion);
    static float getCoseno(float angulo, int &anguloAnimacion);
};


#endif //INC_1942OLDENAIT_TRIGONOMASTER_HPP
