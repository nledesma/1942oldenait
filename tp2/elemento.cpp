#include "elemento.hpp"
Elemento::Elemento(float posX, float posY){
  this->posX = posX;//generarNumeroAleatorio(0,800);
  this->posY = posY;//generarNumeroAleatorio(0,600);
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
	this->figuraElemento->render((int)this->posX, (int)this->posY, renderer);
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
