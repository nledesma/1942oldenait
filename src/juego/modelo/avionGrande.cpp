#include "avionGrande.hpp"

AvionGrande::AvionGrande(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, string idSprite, string idSpriteDisparos, Trayectoria trayectoria){
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
    this->trayectoria = trayectoria;
}

AvionGrande::~AvionGrande(){

}

Disparo* AvionGrande::disparar(){

}

void AvionGrande::mover(float timeStep){

}

void AvionGrande::volverEstadoInicial(){

}
