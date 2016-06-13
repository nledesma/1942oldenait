#include "powerUpAvionesSecundarios.hpp"

PowerUpAvionesSecundarios::PowerUpAvionesSecundarios(float posicionX, float posicionY, int valor) {
	this->tipo = TIPO_POWERUP_AVIONES_SECUNDARIOS;
  	this->valor = valor;
  	this->posX = posicionX;
  	this->posY = posicionY;
	this->posXInicial = posicionX;
	this->posYInicial = posicionY;
  	this->estadoAnimacion = POWER_UP_NORMAL;
  	this->idSprite = SPRITE_POWERUP_AVIONES_SECUNDARIOS;
	this->colisionable = new Colisionable(this->posX,this->posY,0,this->tipo);
}

PowerUpAvionesSecundarios::~PowerUpAvionesSecundarios() {}
