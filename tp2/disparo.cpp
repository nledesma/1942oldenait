#include "disparo.hpp"

Disparo::Disparo(){
}
Disparo::~Disparo(){
}

void Disparo::setTipo(string tipo){
	this->tipo = tipo;
}

string Disparo::getTipo(){
	return this->tipo;
}
void Disparo::setVelocidad(int velocidad){
	this->velocidad = velocidad;
}

int Disparo::getVelocidad(){
	return this->velocidad;
}

void Disparo::setIdSprite(string idSprite){
	this->idSprite = idSprite;
}

string Disparo::getIdSprite(){
	return this->idSprite;
}

