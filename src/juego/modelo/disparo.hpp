#ifndef DISPARO_HPP
#define DISPARO_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <pthread.h>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/colisiones/colisionable.hpp"
using namespace std;

#define TIEMPO_EXPLOSION_IMPACTO 0.1

class Disparo {
private:
	float velocidad;
	float posX;
	float posY;
	int nroAvionDisparador;
	pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;
	Colisionable* colisionable;
	bool colisiono;
	float alturaDeMuerte;
	int estado;
	float contadorExplosionImpacto;
	int numeroDeAvion;

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
	int getEstado();
	void setAvion(int nroAvion);
	int getNroAvion();
	Colisionable* getColisionable();
	void colisionar();
    int getNumeroDeAvion();
};
#endif
