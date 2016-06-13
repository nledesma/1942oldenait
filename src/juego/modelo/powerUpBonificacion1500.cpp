#include "powerUpBonificacion1500.hpp"

PowerUpBonificacion1500::PowerUpBonificacion1500(float posX, float posY, int valor) {
	   this->tipo = TIPO_POWERUP_BONIFICACION_1500;
     this->valor = valor;
		 this->posX = posX;
		 this->posY = posY;
		 this->posXInicial = posX;
		 this->posYInicial = posY;
		 this->estadoAnimacion = POWER_UP_NORMAL;
		 this->idSprite = SPRITE_POWERUP_BONIFICACION_1500;
		 this->colisionable = new Colisionable(this->posX,this->posY,0,this->tipo);
}

PowerUpBonificacion1500::~PowerUpBonificacion1500() {}
