#include "avionDeEscuadron.hpp"

AvionDeEscuadron::AvionDeEscuadron(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, string idSprite, string idSpriteDisparos, Trayectoria trayectoria){
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

AvionDeEscuadron::~AvionDeEscuadron(){

}

Disparo* AvionDeEscuadron::disparar(){

}

void AvionDeEscuadron::mover(float timeStep){

}

void AvionDeEscuadron::volverEstadoInicial(){

}
