#include "avionMediano.hpp"

AvionMediano::AvionMediano(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->angulo = angulo;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = Trigonomaster::getSpriteAngulo(angulo);
    this->idSprite = SPRITE_AVION_ENEMIGO_MEDIANO;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->colisionable = new Colisionable(this->posX, this->posY, angulo, TIPO_AVION_MEDIANO);
    this->tipoAvion = TIPO_AVION_MEDIANO;
}

AvionMediano::~AvionMediano(){

}

int AvionMediano::getAncho() {
    return ANCHO_ENEMIGO_MEDIANO;
}

int AvionMediano::getAlto() {
    return ALTO_ENEMIGO_MEDIANO;
}

vector<DisparoEnemigo*> AvionMediano::disparar(){  vector<DisparoEnemigo*> disparos; return disparos;  }