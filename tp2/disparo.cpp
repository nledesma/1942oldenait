#include "disparo.hpp"

Disparo::Disparo(float posX, float posY, float velocidad, string path, SDL_Renderer * renderer){
	this->velocidad = velocidad;
	this->figuraDisparo = new Figura();
	this->posX = posX;
	this->posY = posY;
	this->cargarImagen(path, renderer);
	this->alturaImagen = 40;
}

Disparo::~Disparo(){
}

void Disparo::setTipo(string tipo){
	this->tipo = tipo;
}

string Disparo::getTipo(){
	return this->tipo;
}

void Disparo::setVelocidad(float velocidad){
	this->velocidad = velocidad;
}

float Disparo::getVelocidad(){
	return this->velocidad;
}

void Disparo::setIdSprite(string idSprite){
	this->idSprite = idSprite;
}

string Disparo::getIdSprite(){
	return this->idSprite;
}

void Disparo::render(SDL_Renderer * renderer) {
	this->figuraDisparo->render((int)this->posX, (int)this->posY, renderer, NULL);
}

int Disparo::cargarImagen(string path, SDL_Renderer* renderer){
	if(!this->figuraDisparo->loadFromFile(path, renderer)){
		cout << "Failed" << endl;
		//TODO usar una excepcion
		return 0;
	}
	this->render(renderer);
	return 1;
}

int Disparo::mover(float timeStep){
	this->posY -= this->velocidad * timeStep;
	//If the dot went too far to the left or right
	if( this->posY < -this->alturaImagen){
			//Move back
			return 0;
	}
	return 1;
}
