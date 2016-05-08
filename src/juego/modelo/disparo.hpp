#ifndef DISPARO_HPP
#define DISPARO_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "../../accesorios/codigo.hpp"
using namespace std;

class Disparo {
private:
	float velocidad;
	float posX;
	float posY;

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
};
#endif
