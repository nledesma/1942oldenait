#include "powerUpDosAmetralladoras.hpp"

PowerUpDosAmetralladoras::PowerUpDosAmetralladoras(float posX, float posY, int valor){
	this->tipo = TIPO_POWERUP_DOS_AMETRALLADORAS;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
	this->posXInicial = posX;
	this->posYInicial = posY;
  	this->estadoAnimacion = POWER_UP_NORMAL;
  	this->idSprite = SPRITE_POWERUP_DOS_AMETRALLADORAS;
	this->colisionable = new Colisionable(this->posX,this->posY,0,this->tipo);
}

PowerUpDosAmetralladoras::~PowerUpDosAmetralladoras() { }

//void PowerUpDosAmetralladoras::colisionar(){
//	cout << "Esta por colisionar" << endl;
//	if(this->estadoAnimacion < POWER_UP_COLISIONADO_DOS_AMETRALLADORAS){
//			this->estadoAnimacion = POWER_UP_COLISIONADO_DOS_AMETRALLADORAS;
//	}
//	cout << "Colisiono" << endl;
//}

//void PowerUpDosAmetralladoras::animar(float timeStep){
//	if (this->estadoAnimacion != POWER_UP_COLISIONADO_DOS_AMETRALLADORAS) {
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
