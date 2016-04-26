#include "avion.hpp"

using namespace std;

Avion::Avion(string idSprite,int velocidadDesplazamiento,string idSpriteAnimacion,Disparo unDisparo){
	this->idSprite = idSprite;
	this->velocidadDesplazamiento = velocidadDesplazamiento;
	this->idSpriteAnimacion = idSpriteAnimacion;
	this->disparo = unDisparo;
}

Avion::Avion(){
	this->gAvionTextura = new Figura();
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

int Avion::cargarImagen(string path, SDL_Renderer* renderer){
	if(!this->gAvionTextura->loadFromFile(path, renderer)){
		cout << "Failed" << endl;
		//TODO usar una excepcion
		return 0;
	}
	this->gAvionTextura->render(100, 100, renderer);
	SDL_RenderPresent(renderer);
	return 1;
}

void Avion::cerrar(){
	this->gAvionTextura->free();
}

SDL_Renderer* Avion::getAvionRenderer(){
	return this->gAvionRenderer;
}

Figura* Avion::getAvionTextura(){
	return this->gAvionTextura;
}
