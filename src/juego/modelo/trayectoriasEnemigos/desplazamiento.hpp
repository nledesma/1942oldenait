#ifndef INC_1942OLDENAIT_DESPLAZAMIENTO_HPP
#define INC_1942OLDENAIT_DESPLAZAMIENTO_HPP

#include "../../../accesorios/trigonomaster.hpp"
#include "tipoMovimiento.hpp"
#include <iostream>

using namespace std;

class Desplazamiento : public TipoMovimiento {
private:
    float cantidadTimesteps;
    float cantidadTimestepsInicial;
    float velocidadAngular;
    float velocidadAngularInicial;
public:
    Desplazamiento(float cantidadTimesteps, float velocidadAngular);

    bool mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep);
    void setEstadoInicial();
};


#endif //INC_1942OLDENAIT_DESPLAZAMIENTO_HPP
