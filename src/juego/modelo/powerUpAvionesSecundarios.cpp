#include "powerUpAvionesSecundarios.hpp"

PowerUpAvionesSecundarios::PowerUpAvionesSecundarios(float posicionX, float posicionY, int valor) {
	this->tipo = TIPO_POWERUP_AVIONES_SECUNDARIOS;
  	this->valor = valor;
  	this->posX = posX;
  	this->posY = posY;
	this->posXInicial = posX;
	this->posYInicial = posY;
  	this->estadoAnimacion = POWER_UP_NORMAL;
  	this->idSprite = SPRITE_POWERUP_AVIONES_SECUNDARIOS;
	this->colisionable = new Colisionable(this->posX,this->posY,0,this->tipo);
}

PowerUpAvionesSecundarios::~PowerUpAvionesSecundarios() {}

//void PowerUpAvionesSecundarios::colisionar(){
//	if(this->estadoAnimacion < POWER_UP_COLISIONADO_AVIONES_SECUNDARIOS){
//			this->estadoAnimacion = POWER_UP_COLISIONADO_AVIONES_SECUNDARIOS;
//	}
//	cout << "Colisiono" << endl;
//}

//void PowerUpAvionesSecundarios::animar(float timeStep){
//	if (this->estadoAnimacion != POWER_UP_COLISIONADO_AVIONES_SECUNDARIOS) {
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
