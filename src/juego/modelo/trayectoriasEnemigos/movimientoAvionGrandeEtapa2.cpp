#include "movimientoAvionGrandeEtapa2.hpp"
#include "../../../accesorios/codigo.hpp"

MovimientoAvionGrandeEtapa2::MovimientoAvionGrandeEtapa2() { }

MovimientoAvionGrandeEtapa2::~MovimientoAvionGrandeEtapa2() { }

bool MovimientoAvionGrandeEtapa2::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep) {
    float velocidadAusar = velocidad;
    if (angulo == 180)
        velocidadAusar = - velocidad;

    if ((posX + timestep * velocidadAusar) >= (ANCHO_ESCENARIO - ANCHO_ENEMIGO_GRANDE) ||
            (posX + timestep * velocidadAusar) <= 0){
        angulo = switchAngulo(angulo);
        posX = posX - velocidadAusar * timestep;
    } else {
        posX = posX + velocidadAusar * timestep;
    }
    return false;
}

float MovimientoAvionGrandeEtapa2::switchAngulo(float angulo) {
    if (angulo == 180){
        return 0;
    } else {
        return 180;
    }
}