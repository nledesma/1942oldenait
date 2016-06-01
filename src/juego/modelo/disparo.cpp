#include "disparo.hpp"

Disparo::Disparo(float posX, float posY, float velocidad){

    this->posX = posX;
    this->posY = posY;
	this->velocidad = velocidad;
    this->colisionable = new Colisionable(this->posX, this->posY, ANCHO_DISPARO_COMUN, ALTO_DISPARO_COMUN);
    this->colisiono = false;
}

Disparo::~Disparo(){
}

void Disparo::setVelocidad(float velocidad){
	this->velocidad = velocidad;
}

float Disparo::getVelocidad(){
	return this->velocidad;
}

int Disparo::mover(float timeStep){
    if(!this->colisiono){
        pthread_mutex_lock(&this->mutexMover);
        int retorno;
        this->posY -= this->velocidad * timeStep;
        if( this->posY < - ALTO_DISPARO_COMUN){
            retorno = 0;
        } else {
            retorno = 1;
        }
        this->colisionable->setPosY(this->posY);
        pthread_mutex_unlock(&this->mutexMover);
        return retorno;
    }
    return 0;
}

void Disparo::setPosY(float posY){
    this->posY = posY;
}

float Disparo::getPosY(){
    return this->posY;
}

void Disparo::setPosX(float posX){
    this->posX = posX;
}

float Disparo::getPosX(){
    return this->posX;
}

int Disparo::getAlto(){
    return ALTO_DISPARO_COMUN;
}

int Disparo::getAncho(){
    return ANCHO_DISPARO_COMUN;
}

Colisionable* Disparo::getColisionable(){
    return this->colisionable;
}

void Disparo::colisionar(){
    this->colisiono = true;
}
