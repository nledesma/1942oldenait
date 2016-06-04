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
    this->colisionable = new Colisionable(this->posX, this->posY, angulo, TIPO_AVION_PEQUENIO);
    this->contador = CONTADOR_INICIAL;
}

AvionPequenio::~AvionPequenio(){
    delete this->colisionable;
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