#include "movimientoAvionGrandeEtapa1.hpp"

MovimientoAvionGrandeEtapa1::~MovimientoAvionGrandeEtapa1(){ }

MovimientoAvionGrandeEtapa1::MovimientoAvionGrandeEtapa1(float yTope){
    this->yTope = yTope;
}

bool MovimientoAvionGrandeEtapa1::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep) {
    posY -= velocidad*timestep;
    if (posY < this->yTope){
        angulo = 180;
        return true;
    } else {
        return false;
    }
}