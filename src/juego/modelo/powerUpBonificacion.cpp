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

void PowerUpBonificacion::colisionar(){
	cout << "Esta por colisionar" << endl;
	if(this->estadoAnimacion < POWER_UP_COLISIONADO_BONIFICACION){
			this->estadoAnimacion = POWER_UP_COLISIONADO_BONIFICACION;
	}
	cout << "Colisiono" << endl;
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
