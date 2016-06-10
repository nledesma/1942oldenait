#include "powerUp.hpp"

PowerUp::~PowerUp(){

}

/*
void PowerUp::aplicarPowerUp(){}
*/
Colisionable* PowerUp::getColisionable(){
    return this->colisionable;
}

void PowerUp::colisionar(){

}

int PowerUp::getEstadoAnimacion(){
    return this->estadoAnimacion;
}

int PowerUp::getTipoPowerUp() {
    return this->tipo;
}

float PowerUp::getPosicionX(){
    pthread_mutex_lock(&this->mutexMover);
    float posX = this->posX;
    pthread_mutex_unlock(&this->mutexMover);
    return posX;
}

float PowerUp::getPosicionY(){
    pthread_mutex_lock(&this->mutexMover);
    float posY = this->posY;
    pthread_mutex_unlock(&this->mutexMover);
    return posY;
}

int PowerUp::getValor(){
    return this->valor;
}

string PowerUp::getIdSprite(){
      return this->idSprite;
  }

void PowerUp::mover(float timeStep, float velocidadY){
    pthread_mutex_lock(&this->mutexMover);
    this->posY += velocidadY * timeStep;
    this->animar(timeStep);
    pthread_mutex_unlock(&this->mutexMover);
}

void PowerUp::animar(float timeStep) {

}


void PowerUp::volverEstadoInicial(){
    this->posX = posXInicial;
    this->posY = posYInicial;
}
