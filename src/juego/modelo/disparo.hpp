#ifndef DISPARO_HPP
#define DISPARO_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <pthread.h>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/colisiones/colisionable.hpp"
using namespace std;

class Disparo {
private:
	float velocidad;
	float posX;
	float posY;
	pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;
	Colisionable* colisionable;
public:
	Disparo(float posX, float posY, float velocidad);
	~Disparo();
	void setVelocidad(float velocidad);
	float getVelocidad();
	int mover(float timeStep);
  	void setPosY(float posY);
  	float getPosY();
  	void setPosX(float posX);
  	float getPosX();
  	int getAlto();
  	int getAncho();
		Colisionable* getColisionable();
		void colisionar();
};
#endif
