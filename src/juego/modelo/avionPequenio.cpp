#include "avionPequenio.hpp"

AvionPequenio::AvionPequenio(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, string idSprite, string idSpriteDisparos){
    this->posX = posX;
    this->posY = posY;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->velocidadX = 0;
    this->velocidadY = 0;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = ESTADO_NORMAL;
    this->idSprite = idSprite;
    this->idSpriteDisparos = idSpriteDisparos;
}

AvionPequenio::~AvionPequenio(){

}

Disparo* AvionPequenio::disparar(){

}

void AvionPequenio::mover(float timeStep){

}

void AvionPequenio::volverEstadoInicial(){

}
