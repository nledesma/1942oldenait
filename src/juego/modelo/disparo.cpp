#include "disparo.hpp"

Disparo::Disparo(float posX, float posY, float velocidad){

    this->posX = posX;
    this->posY = posY;
	this->velocidad = velocidad;
}

Disparo::~Disparo(){
}

void Disparo::setVelocidad(float velocidad){
	this->velocidad = velocidad;
}

float Disparo::getVelocidad(){
	return this->velocidad;
}

//TODO reever el return de este metodo
int Disparo::mover(float timeStep){
	this->posY -= this->velocidad * timeStep;
	//If the dot went too far to the left or right
	if( this->posY < - ALTO_DISPARO_COMUN){
			//Move back
			return 0;
	}
	return 1;
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
