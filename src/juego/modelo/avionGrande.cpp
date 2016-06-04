#include "avionGrande.hpp"

AvionGrande::AvionGrande(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->angulo = angulo;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = AVION_ENEMIGO_GRANDE_NORMAL;
    this->idSprite = SPRITE_AVION_ENEMIGO_GRANDE;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->tipoAvion = TIPO_AVION_GRANDE;
}

AvionGrande::~AvionGrande(){

}

Disparo* AvionGrande::disparar(){
    return NULL;
}

int AvionGrande::getAncho() {
    return ANCHO_ENEMIGO_GRANDE;
}

int AvionGrande::getAlto() {
    return ALTO_ENEMIGO_GRANDE;
}

int AvionGrande::mover(float timeStep){
    return AvionEnemigo::mover(timeStep);
}

float AvionGrande::getVelocidad(){
    return AvionEnemigo::getVelocidad();
}

float AvionGrande::getPosicionX(){
    return AvionEnemigo::getPosicionX();
}

float AvionGrande::getPosicionY(){
    return AvionEnemigo::getPosicionY();
}

float AvionGrande::getAngulo(){
    return AvionEnemigo::getAngulo();
}

int AvionGrande::getEstadoAnimacion(){
    return AvionEnemigo::getEstadoAnimacion();
}

int AvionGrande::getTipoAvion(){
    return AvionEnemigo::getTipoAvion();
}

int AvionGrande::getAnchoDisparo(){
    return AvionEnemigo::getAnchoDisparo();
}

int AvionGrande::getAltoDisparo(){
    return AvionEnemigo::getAltoDisparo();
}

string AvionGrande::getIdSprite(){
    return AvionEnemigo::getIdSprite();
}

string AvionGrande::getIdSpriteDisparos(){
    return AvionEnemigo::getIdSpriteDisparos();
}
