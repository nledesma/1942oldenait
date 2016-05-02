#ifndef DISPARO_HPP
#define DISPARO_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "figura.hpp"

using namespace std;

class Disparo {
private:
	string tipo;
	float velocidad;
	string idSprite;
	Figura * figuraDisparo;
	float posX;
	float posY;
	int alturaImagen;

public:
	Disparo(float poX, float posY, float velocidad, string path, SDL_Renderer * renderer);
	~Disparo();
	int cargarImagen(string path, SDL_Renderer * renderer);
	void setTipo(string tipo);
	string getTipo();
	void setVelocidad(float velocidad);
	float getVelocidad();
	void setIdSprite(string idSprite);
	int mover(float timeStep);
	string getIdSprite();
	void render(SDL_Renderer * renderer);
};
#endif
