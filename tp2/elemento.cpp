#include "elemento.hpp"
Elemento::Elemento(float posX, float posY, float velocidadDesplazamientoY,string spriteId){
  this->spriteId = spriteId;
  this->posX = posX;//generarNumeroAleatorio(0,800);
  this->posY = posY;//generarNumeroAleatorio(0,600);
  this->velocidadDesplazamientoY = velocidadDesplazamientoY;
  this->figuraElemento = new Figura();
}

float Elemento::generarNumeroAleatorio(float a, float b) {
  srand((float)time(NULL));
  float numero = ((float) rand()) / (float) RAND_MAX;
  float resta = b - a;
  float numeroRandom = numero * resta;
  return a + numeroRandom;
}

void Elemento::render(SDL_Renderer* renderer){
  this->figuraElemento->render((int)this->posX, (int)this->posY, renderer, NULL);
}

int Elemento::cargarImagen(string path, SDL_Renderer* renderer){
	if(!this->figuraElemento->loadFromFile(path, renderer)){
		cout << "Failed" << endl;
		//TODO usar una excepcion
		return 0;
	}
	this->render(renderer);
	return 1;
}

string Elemento::getSpriteId(){
  return this->spriteId;
}

float Elemento::getPosX(){
  return this->posX;
}

float Elemento::getPosY(){
  return this->posY;
}

float Elemento::getVelocidadDesplazamientoY() {
  return this->velocidadDesplazamientoY;
}

void Elemento::mover(float timeStep){
    this->posY += this->velocidadDesplazamientoY * timeStep;
}

