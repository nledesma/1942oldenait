#include "rutinaLoop.hpp"

void RutinaLoop::mover(float &posX, float &posY, float &velocidad, float &angulo, float timestep) {
    this->transportarAngulo(angulo, timestep);
    float velocidadX = velocidad * Trigonomaster::getCoseno(angulo);
    float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo));
    posX = posX + velocidadX * timestep;
    posY = posY + velocidadY * timestep;
}

void RutinaLoop::transportarAngulo(float &angulo, float timestep) {
    angulo = angulo + timestep * this->velocidadAngular;
    if ( angulo < 0 ){
        angulo = angulo + 360;
    } else if ( angulo > 360 ){
        angulo = angulo - 360;
    }
}
