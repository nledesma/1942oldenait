#ifndef INC_1942OLDENAIT_TRAYECTORIARULO_HPP
#define INC_1942OLDENAIT_TRAYECTORIARULO_HPP

#include "trayectoria.hpp"
#include "desplazamiento.hpp"
#include "giro.hpp"


class TrayectoriaRulo : public Trayectoria {
private:
public:
    TrayectoriaRulo();
    ~TrayectoriaRulo();
    void mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
    void setEstadoInicial();
};




#endif //INC_1942OLDENAIT_TRAYECTORIARULO_HPP
