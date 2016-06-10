#include "powerUpAvionesSecundarios.hpp"

PowerUpAvionesSecundarios::PowerUpAvionesSecundarios(float posicionX, float posicionY, int valor) {
	this->tipo = TIPO_POWERUP_BONIFICACION;
  	this->valor = valor;
  	this->posX = posX;
	this->posY = posY;
	this->posXInicial = posX;
	this->posYInicial = posY;
  	this->estadoAnimacion = POWER_UP_NORMAL;
  	this->idSprite = SPRITE_POWERUP_BONIFICACION;
}

void PowerUpAvionesSecundarios::colisionar(){
	if(this->estadoAnimacion <= POWER_UP_ROTACION_6){
			this->estadoAnimacion = POWER_UP_COLISIONADO;
	}
}

PowerUpAvionesSecundarios::~PowerUpAvionesSecundarios() {}

void PowerUpAvionesSecundarios::animar(float timeStep){
	if (this->estadoAnimacion != POWER_UP_COLISIONADO) {
			if ((this->contadorTiempoAnimacion + timeStep) >= FRECUENCIA_ANIMACION) {
					this->contadorTiempoAnimacion = 0;
					if (this->estadoAnimacion < POWER_UP_ROTACION_6)
							this->estadoAnimacion += 1;
					else
							this->estadoAnimacion = POWER_UP_NORMAL;
			} else {
					this->contadorTiempoAnimacion += timeStep;
			}
	}
}
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
