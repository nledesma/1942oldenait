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
}

PowerUpBonificacion::~PowerUpBonificacion() {}

void PowerUpBonificacion::colisionar(){
	if(this->estadoAnimacion <= POWER_UP_ROTACION_6){
			this->estadoAnimacion = POWER_UP_COLISIONADO_BONIFICACION;
	}
}

void PowerUpBonificacion::animar(float timeStep){
	if (this->estadoAnimacion != POWER_UP_COLISIONADO_BONIFICACION) {
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
