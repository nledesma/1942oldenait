#include "boton.hpp"
Boton::Boton(){
	this->posicion.x = 0;
	this->posicion.y = 0;
	this->figuraBoton = new Figura();
}

int Boton::getPosicionX(){
	return this->posicion.x;
}

int Boton::getPosicionY(){
	return this->posicion.y;
}

void Boton::setPosition(int x, int y){
	posicion.x = x;
	posicion.y = y;
}

Figura* Boton::getFigura(){
	return this->figuraBoton;
}
