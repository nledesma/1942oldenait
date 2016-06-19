#ifndef INC_1942OLDENAIT_TRAYECTORIAIDAYVUELTA_HPP
#define INC_1942OLDENAIT_TRAYECTORIAIDAYVUELTA_HPP

#include "trayectoria.hpp"
#include "desplazamiento.hpp"
#include "giro.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class TrayectoriaIdaYvuelta : public Trayectoria {
private:
    float tiempoIda;
public:
    TrayectoriaIdaYvuelta();
    ~TrayectoriaIdaYvuelta();
    void mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
    void setEstadoInicial();
};


#endif //INC_1942OLDENAIT_TRAYECTORIAIDAYVUELTA_HPP