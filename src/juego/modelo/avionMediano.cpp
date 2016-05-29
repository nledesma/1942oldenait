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