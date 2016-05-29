#include "avionMediano.hpp"

AvionMediano::AvionMediano(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = Trigonomaster::getSpriteAngulo(angulo);
    this->idSprite = SPRITE_AVION_ENEMIGO_MEDIANO;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->tipoAvion = TIPO_AVION_MEDIANO;
}

AvionMediano::~AvionMediano(){

}

Disparo* AvionMediano::disparar(){
    return NULL;
}

int AvionMediano::getAncho() {
    return ANCHO_ENEMIGO_MEDIANO;
}

int AvionMediano::getAlto() {
    return ALTO_ENEMIGO_MEDIANO;
}

int AvionMediano::mover(float timeStep){
    return AvionEnemigo::mover(timeStep);
}

float AvionMediano::getVelocidad(){
    return AvionEnemigo::getVelocidad();
}

float AvionMediano::getPosicionX(){
    return AvionEnemigo::getPosicionX();
}

float AvionMediano::getPosicionY(){
    return AvionEnemigo::getPosicionY();
}

float AvionMediano::getAngulo(){
    return AvionEnemigo::getAngulo();
}

int AvionMediano::getEstadoAnimacion(){
    return AvionEnemigo::getEstadoAnimacion();
}

int AvionMediano::getTipoAvion(){
    return AvionEnemigo::getTipoAvion();
}

int AvionMediano::getAnchoDisparo(){
    return AvionEnemigo::getAnchoDisparo();
}

int AvionMediano::getAltoDisparo(){
    return AvionEnemigo::getAltoDisparo();
}

string AvionMediano::getIdSprite(){
    return AvionEnemigo::getIdSprite();
}

string AvionMediano::getIdSpriteDisparos(){
    return AvionEnemigo::getIdSpriteDisparos();
}