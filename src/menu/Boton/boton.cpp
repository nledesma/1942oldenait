#include "boton.hpp"
Boton::Boton(){
	this->mPosition.x = 0;
	this->mPosition.y = 0;
	this->gButtonSpriteSheetTexture = new Figura();
}

int Boton::getPosicionX(){
	return this->mPosition.x;
}

int Boton::getPosicionY(){
	return this->mPosition.y;
}

void Boton::setPosition(int x, int y){
	mPosition.x = x;
	mPosition.y = y;
}

Figura* Boton::getFigura(){
	return this->gButtonSpriteSheetTexture;
}
