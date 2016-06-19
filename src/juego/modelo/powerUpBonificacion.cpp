#include "powerUpBonificacion.hpp"

PowerUpBonificacion::PowerUpBonificacion(float posX, float posY, int valor) {
	this->tipo = TIPO_POWERUP_BONIFICACION;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
	this->posXInicial = posX;
	this->posYInicial = posY;
  	this->estadoAnimacion = POWER_UP_NORMAL;
  	this->idSprite = SPRITE_POWERUP_BONIFICACION;
	this->colisionable = new Colisionable(this->posX,this->posY,0,this->tipo);
}

PowerUpBonificacion::~PowerUpBonificacion() {}

void PowerUpBonificacion::aplicarPowerUp(){

}
