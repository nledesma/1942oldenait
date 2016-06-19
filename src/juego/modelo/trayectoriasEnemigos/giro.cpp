#include "giro.hpp"

Giro::Giro(float arg1, float arg2) {
    this->anguloAbarrer = arg1;
    this->anguloAbarrerInicial = arg1;
    this->velocidadAngular = arg2;
    this->velocidadAngularInicial = arg2;
}

Giro::~Giro() { }

bool Giro::mover(float &posX, float &posY, float &velocidad, float &angulo,
                       int &estadoAnimacion, float timestep) {
    float anguloBarrido = this->transportarAngulo(angulo, this->velocidadAngular, timestep);
    float velocidadX = velocidad * Trigonomaster::getCoseno(angulo, estadoAnimacion);
    float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo, estadoAnimacion));
    posX = posX + velocidadX * timestep;
    posY = posY + velocidadY * timestep;

    this->anguloAbarrer = this->anguloAbarrer - anguloBarrido;

    return  (this->anguloAbarrer <= 0);
}

float Giro::transportarAngulo(float &angulo, float velocidadAngular, float timestep) {
    float anguloBarrido = timestep * velocidadAngular;
    angulo = angulo + anguloBarrido;
    if ( angulo < 0 ){
        angulo = angulo + 360;
    } else if ( angulo > 360 ){
        angulo = angulo - 360;
    }

    if (anguloBarrido >= 0)
        return anguloBarrido;
     else
        return -anguloBarrido;
}

void Giro::setEstadoInicial() {
    this->anguloAbarrer = this->anguloAbarrerInicial;
    this->velocidadAngular = this->velocidadAngularInicial;
}