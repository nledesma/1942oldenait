#ifndef DISPARO_HPP
#define DISPARO_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "figura.hpp"

using namespace std;

class Disparo {
private:
	float velocidad;
	float posX;
	float posY;

public:
  	static const int DISPARO_ANCHO = ANCHO_DISPARO_COMUN;
  	static const int DISPARO_ALTO = ALTO_DISPARO_COMUN;
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
};
#endif
