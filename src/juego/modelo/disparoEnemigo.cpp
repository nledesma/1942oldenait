#include "disparoEnemigo.hpp"

DisparoEnemigo::DisparoEnemigo(float posX, float posY, float velocidad,float versorX, float versorY){

    this->posX = posX;
    this->posY = posY;
    this->velocidad = velocidad;
    this->versorX = versorX;
    this->versorY = versorY;
    this->colisionable = new Colisionable(this->posX, this->posY, 0, TIPO_DISPARO_ENEMIGO);
    this->colisiono = false;
}

DisparoEnemigo::~DisparoEnemigo(){
}

float DisparoEnemigo::getVelocidad(){
    return this->velocidad;
}

int DisparoEnemigo::mover(float timeStep){
    pthread_mutex_lock(&this->mutexMover);
    int retorno = 0;
    if(!this->colisiono){
        this->posX += this->velocidad * this->versorX * timeStep;
        this->posY += this->velocidad * this->versorY * timeStep;
        if( this->posY < - ALTO_DISPARO_ENEMIGO){
            retorno = 0;
        } else {
            retorno = 1;
        }
        this->colisionable->mover(this->posX, this->posY, 0);
    }
    pthread_mutex_unlock(&this->mutexMover);
    return retorno;
}

void DisparoEnemigo::setPosY(float posY){
    this->posY = posY;
}

float DisparoEnemigo::getPosY(){
    return this->posY;
}

void DisparoEnemigo::setPosX(float posX){
    this->posX = posX;
}

float DisparoEnemigo::getPosX(){
    return this->posX;
}

int DisparoEnemigo::getAlto(){
    return ALTO_DISPARO_ENEMIGO;
}

int DisparoEnemigo::getAncho(){
    return ANCHO_DISPARO_ENEMIGO;
}

void DisparoEnemigo::setAvion(int nroAvion){
    nroAvionDisparador = nroAvion;
}

int DisparoEnemigo::getNroAvion(){
    return nroAvionDisparador;
}

Colisionable* DisparoEnemigo::getColisionable(){
    return this->colisionable;
}

void DisparoEnemigo::colisionar(){
    this->colisiono = true;
}