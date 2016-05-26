#include "giro.hpp"

void Giro::girarAngulo(float &posX, float &posY, float &velocidad, float &angulo, float &anguloAbarrer,
                       int &estadoAnimacion, float velocidadAngular, float timestep) {
    float anguloBarrido = this->transportarAngulo(angulo, velocidadAngular, timestep);
    float velocidadX = velocidad * Trigonomaster::getCoseno(angulo, estadoAnimacion);
    float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo, estadoAnimacion));
    posX = posX + velocidadX * timestep;
    posY = posY + velocidadY * timestep;

    anguloAbarrer = anguloAbarrer - anguloBarrido;
}

float Giro::transportarAngulo(float &angulo, float velocidadAngular, float timestep) {
    float anguloBarrido = timestep * velocidadAngular;
    angulo = angulo + anguloBarrido;
    if ( angulo < 0 ){
        angulo = angulo + 360;
    } else if ( angulo > 360 ){
        angulo = angulo - 360;
    }
    return anguloBarrido;
}