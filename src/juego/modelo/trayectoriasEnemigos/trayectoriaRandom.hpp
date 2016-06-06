#ifndef INC_1942OLDENAIT_TRAYECTORIARANDOM_HPP
#define INC_1942OLDENAIT_TRAYECTORIARANDOM_HPP

#include "trayectoria.hpp"
#include "desplazamiento.hpp"
#include "giro.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class TrayectoriaRandom : public Trayectoria {
private:
public:
    TrayectoriaRandom();
    ~TrayectoriaRandom();
    void mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);

};


#endif //INC_1942OLDENAIT_TRAYECTORIARANDOM_HPP