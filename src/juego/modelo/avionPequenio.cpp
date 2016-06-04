#include "avionPequenio.hpp"

AvionPequenio::AvionPequenio(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->velocidad = velocidad;
    this->angulo = angulo;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = Trigonomaster::getSpriteAngulo(angulo);
    this->idSprite = SPRITE_AVION_ENEMIGO_PEQUENIO;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->tipoAvion = TIPO_AVION_PEQUENIO;
}

AvionPequenio::~AvionPequenio(){

}

Disparo* AvionPequenio::disparar(){
    return NULL;
}

int AvionPequenio::getAncho() {
    return ANCHO_ENEMIGO_PEQUENIO;
}

int AvionPequenio::getAlto() {
    return ALTO_ENEMIGO_PEQUENIO;
}

int AvionPequenio::mover(float timeStep){
    return AvionEnemigo::mover(timeStep);
}

float AvionPequenio::getVelocidad(){
    return AvionEnemigo::getVelocidad();
}

float AvionPequenio::getPosicionX(){
    return AvionEnemigo::getPosicionX();
}

float AvionPequenio::getPosicionY(){
    return AvionEnemigo::getPosicionY();
}

float AvionPequenio::getAngulo(){
    return AvionEnemigo::getAngulo();
}

int AvionPequenio::getEstadoAnimacion(){
    return AvionEnemigo::getEstadoAnimacion();
}

int AvionPequenio::getTipoAvion(){
    return AvionEnemigo::getTipoAvion();
}

int AvionPequenio::getAnchoDisparo(){
    return AvionEnemigo::getAnchoDisparo();
}

int AvionPequenio::getAltoDisparo(){
    return AvionEnemigo::getAltoDisparo();
}

string AvionPequenio::getIdSprite(){
    return AvionEnemigo::getIdSprite();
}

string AvionPequenio::getIdSpriteDisparos(){
    return AvionEnemigo::getIdSpriteDisparos();
}