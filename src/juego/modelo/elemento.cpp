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
    pthread_mutex_lock(&this->mutexMover);
    float posicionX = this->posX;
    pthread_mutex_unlock(&this->mutexMover);
    return posicionX;
}

float Elemento::getPosY(){
    pthread_mutex_lock(&this->mutexMover);
    float posicionY = this->posY;
    pthread_mutex_unlock(&this->mutexMover);
    return posicionY;
}

void Elemento::volverEstadoInicial(){
    this->posX = posXInicial;
    this->posY = posYInicial;
}

string Elemento::getIdSprite(){
    return this->idSprite;
}
