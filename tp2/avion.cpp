#include "avion.hpp"

using namespace std;

Avion::Avion(string idSprite,int velocidadDesplazamiento,string idSpriteAnimacion,Disparo unDisparo){
	this->idSprite = idSprite;
	this->velocidadDesplazamiento = velocidadDesplazamiento;
	this->idSpriteAnimacion = idSpriteAnimacion;
	this->disparo = unDisparo;
}

Avion::~Avion(){

}

string Avion::getIdSprite(){
	return this->idSprite;
}

void Avion::setIdSprite(string idSprite){
	this->idSprite = idSprite;
}

int Avion::getVelocidadDesplazamiento(){
	return this->velocidadDesplazamiento;
}

void Avion::setVelocidadDesplazamiento(int velocidadDesplazamiento){
	this->velocidadDesplazamiento = velocidadDesplazamiento;
}

string Avion::getIdSpriteAnimacion(){
	return this->idSpriteAnimacion;
}

void Avion::setIdSpriteAnimacion(string idSpriteAnimacion){
	this->idSpriteAnimacion = idSpriteAnimacion;
}
Disparo Avion::getDisparo() {
	return this->disparo;
}

void Avion::setDisparo(Disparo unDisparo) {
	this->disparo = unDisparo;
}

void Avion::mover(int tecla){
}

