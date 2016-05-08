#include "elemento.hpp"

Elemento::Elemento(float posX, float posY, string idSprite){
    this->posX = posX;
    this->posY = posY;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->idSprite = idSprite;
}

void Elemento::mover(float timeStep, float velocidadY){
    this->posY += velocidadY * timeStep;
}

float Elemento::getPosX(){
    return this->posX;
}

float Elemento::getPosY(){
    return this->posY;
}

void Elemento::volverEstadoInicial(){
    this->posX = posXInicial;
    this->posY = posYInicial;
}

string Elemento::getIdSprite(){
    return this->idSprite;
}
