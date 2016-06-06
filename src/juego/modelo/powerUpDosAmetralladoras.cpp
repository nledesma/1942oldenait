#include "powerUpDosAmetralladoras.hpp"

PowerUpDosAmetralladoras::PowerUpDosAmetralladoras(float posX, float posY, int valor){
	this->tipo = TIPO_POWERUP_DOS_AMETRALLADORAS;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
  	this->estadoAnimacion = POWER_UP_DOS_AMETRALLADORAS_NORMAL;
  	this->idSprite = SPRITE_POWERUP_DOS_AMETRALLADORAS;
}

PowerUpDosAmetralladoras::~PowerUpDosAmetralladoras() { }

/*
powerUpDosAmetralladoras::aplicarPowerUp(){}

int powerUpDosAmetralladoras::getAncho(){
	return this->ancho;
}

int powerUpDosAmetralladoras::getAlto(){
	return this->alto;
}

float powerUpDosAmetralladoras::getPosicionX(){
	return this->posX;
}

float powerUpDosAmetralladoras::getPosicionY(){
	return this->posY;
}

int powerUpDosAmetralladoras::getEstadoAnimacion(){
	return this->estadoAnimacion;
}

int powerUpDosAmetralladoras::getTipo(){
	return this->tipo;
}

string powerUpDosAmetralladoras::getIdSprite(){
	return this->idSprite;
}*/
