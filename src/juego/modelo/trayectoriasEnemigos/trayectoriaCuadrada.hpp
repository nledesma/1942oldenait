#ifndef INC_1942OLDENAIT_TRAYECTORIACUADRADA_HPP
#define INC_1942OLDENAIT_TRAYECTORIACUADRADA_HPP

#include "trayectoria.hpp"
#include "desplazamiento.hpp"
#include "giro.hpp"


class TrayectoriaCuadrada : public Trayectoria {
private:
public:
    TrayectoriaCuadrada();
    ~TrayectoriaCuadrada();
    void mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);

};


#endif //INC_1942OLDENAIT_TRAYECTORIACUADRADA_HPP
