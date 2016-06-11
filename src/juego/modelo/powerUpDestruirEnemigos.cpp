
#include "powerUpDestruirEnemigos.hpp"

PowerUpDestruirEnemigos::PowerUpDestruirEnemigos(float posicionX, float posicionY, int valor){
	this->tipo = TIPO_POWERUP_DESTRUIR_ENEMIGOS;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
		this->posXInicial = posX;
		this->posYInicial = posY;
  	this->estadoAnimacion = POWER_UP_NORMAL;
  	this->idSprite = SPRITE_POWERUP_DESTRUIR_ENEMIGOS;
	this->colisionable = new Colisionable(this->posX,this->posY,0,this->tipo);
}

PowerUpDestruirEnemigos::~PowerUpDestruirEnemigos() { }

//void PowerUpDestruirEnemigos::colisionar(){
//	cout << "Esta por colisionar" << endl;
//	if(this->estadoAnimacion < POWER_UP_COLISIONADO_DESTRUIR_ENEMIGOS){
//			this->estadoAnimacion = POWER_UP_COLISIONADO_DESTRUIR_ENEMIGOS;
//	}
//	cout << "Colisiono" << endl;
//}

//void PowerUpDestruirEnemigos::animar(float timeStep){
//	if (this->estadoAnimacion != POWER_UP_COLISIONADO_DESTRUIR_ENEMIGOS) {
//			if ((this->contadorTiempoAnimacion + timeStep) >= FRECUENCIA_ANIMACION) {
//					this->contadorTiempoAnimacion = 0;
//					if (this->estadoAnimacion < POWER_UP_ROTACION_6)
//							this->estadoAnimacion += 1;
//					else
//							this->estadoAnimacion = POWER_UP_NORMAL;
//			} else {
//					this->contadorTiempoAnimacion += timeStep;
//			}
//	}
//}
