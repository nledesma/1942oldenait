#include "powerUpBonificacion.hpp"

PowerUpBonificacion::PowerUpBonificacion(float posX, float posY, int valor) {
		this->tipo = TIPO_POWERUP_BONIFICACION;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
		this->posXInicial = posX;
		this->posYInicial = posY;
  	this->estadoAnimacion = POWER_UP_BONIFICACION_NORMAL;
  	this->idSprite = SPRITE_POWERUP_BONIFICACION;
}

//PowerUpBonificacion::~PowerUpBonificacion() {}

/*
powerUpBonificacion::aplicarPowerUp(){

}

int powerUpBonificacion::getAncho(){
	return this->ancho;
}

int powerUpBonificacion::getAlto(){
	return this->alto;
}

float powerUpBonificacion::getPosicionX(){
	return this->posX;
}

float powerUpBonificacion::getPosicionY(){
	return this->posY;
}

int powerUpBonificacion::getEstadoAnimacion(){
	return this->estadoAnimacion;
}

int powerUpBonificacion::getTipo(){
	return this->tipo;
}

string powerUpBonificacion::getIdSprite(){
	return this->idSprite;
}*/
