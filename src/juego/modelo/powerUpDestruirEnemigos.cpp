
#include "powerUpDestruirEnemigos.hpp"

PowerUpDestruirEnemigos::PowerUpDestruirEnemigos(float posicionX, float posicionY, int valor){
	this->tipo = TIPO_POWERUP_BONIFICACION;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
  	this->estadoAnimacion = POWER_UP_BONIFICACION_NORMAL;
  	this->idSprite = SPRITE_POWERUP_BONIFICACION;
}

PowerUpDestruirEnemigos::~PowerUpDestruirEnemigos() { }

/*
powerUpDestruirEnemigos::aplicarPowerUp(){}

int powerUpDestruirEnemigos::getAncho(){
	return this->ancho;
}

int powerUpDestruirEnemigos::getAlto(){
	return this->alto;
}

float powerUpDestruirEnemigos::getPosicionX(){
	return this->posX;
}

float powerUpDestruirEnemigos::getPosicionY(){
	return this->posY;
}

int powerUpDestruirEnemigos::getEstadoAnimacion(){
	return this->estadoAnimacion;
}

int powerUpDestruirEnemigos::getTipo(){
	return this->tipo;
}

string powerUpDestruirEnemigos::getIdSprite(){
	return this->idSprite;
}
*/
