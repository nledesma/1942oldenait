
#include "powerUpDestruirEnemigos.hpp"

PowerUpDestruirEnemigos::PowerUpDestruirEnemigos(float posicionX, float posicionY, int valor){
	this->tipo = TIPO_POWERUP_BONIFICACION;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
		this->posXInicial = posX;
		this->posYInicial = posY;
  	this->estadoAnimacion = POWER_UP_NORMAL;
  	this->idSprite = SPRITE_POWERUP_BONIFICACION;
}

PowerUpDestruirEnemigos::~PowerUpDestruirEnemigos() { }

void PowerUpDestruirEnemigos::colisionar(){
	if(this->estadoAnimacion <= POWER_UP_ROTACION_6){
			this->estadoAnimacion = POWER_UP_COLISIONADO_DESTRUIR_ENEMIGOS;
	}
}

void PowerUpDestruirEnemigos::animar(float timeStep){
	if (this->estadoAnimacion != POWER_UP_COLISIONADO_DESTRUIR_ENEMIGOS) {
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
