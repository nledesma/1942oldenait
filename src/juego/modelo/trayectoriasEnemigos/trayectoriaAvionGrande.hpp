#ifndef INC_1942OLDENAIT_TRAYECTORIAAVIONGRANDE_HPP
#define INC_1942OLDENAIT_TRAYECTORIAAVIONGRANDE_HPP


#include "trayectoria.hpp"
#include "desplazamiento.hpp"
#include "giro.hpp"


class TrayectoriaAvionGrande : public Trayectoria {
private:
public:
    TrayectoriaAvionGrande();
    ~TrayectoriaAvionGrande();
    void mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
    void setEstadoInicial();
};


#endif //INC_1942OLDENAIT_TRAYECTORIAAVIONGRANDE_HPP
