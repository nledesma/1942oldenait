#include "powerUpAvionesSecundarios.hpp"

PowerUpAvionesSecundarios::PowerUpAvionesSecundarios(float posicionX, float posicionY, int valor) {
		this->tipo = TIPO_POWERUP_BONIFICACION;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
		this->posXInicial = posX;
		this->posYInicial = posY;
  	this->estadoAnimacion = POWER_UP_BONIFICACION_NORMAL;
  	this->idSprite = SPRITE_POWERUP_BONIFICACION;
}

//PowerUpAvionesSecundarios::~PowerUpAvionesSecundarios() {}

/*
powerUpAvionesSecundarios::aplicarPowerUp(){

}

int powerUpAvionesSecundarios::getAncho(){
	return this->ancho;
}

int powerUpAvionesSecundarios::getAlto(){
	return this->alto;
}

float powerUpAvionesSecundarios::getPosicionX(){
	return this->posX;
}

float powerUpAvionesSecundarios::getPosicionY(){
	return this->posY;
}

int powerUpAvionesSecundarios::getEstadoAnimacion(){
	return this->estadoAnimacion;
}

int powerUpAvionesSecundarios::getTipo(){
	return this->tipo;
}

string powerUpAvionesSecundarios::getIdSprite(){
	return this->idSprite;
}
*/
