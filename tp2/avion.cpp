#include "avion.hpp"

using namespace std;

Avion::Avion(string idSprite,int velocidadDesplazamiento,string idSpriteAnimacion,Disparo unDisparo){
	this->idSprite = idSprite;
	this->velocidadDesplazamiento = velocidadDesplazamiento;
	this->idSpriteAnimacion = idSpriteAnimacion;
	this->disparo = unDisparo;
}

Avion::Avion(){

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

bool Avion::cargarImagen(){
	//Loading success flag
	//bool success = true;
	//Load Foo' texture
	//if(!gAvionTextura.loadFromFile("foo.png")){
		//cout << "Failed" << endl;
		//TODO usar una excepcion
		//success = false;
	//}
	//return success;
	return true;
}

void Avion::cerrar(){
	gAvionTextura.free();
}

SDL_Renderer* Avion::getAvionRenderer(){
	return this->gAvionRenderer;
}

ContenedorTextura Avion::getAvionTextura(){
	return this->gAvionTextura;
}
