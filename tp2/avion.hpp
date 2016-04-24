#ifndef AVION_HPP
#define AVION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "disparo.hpp"
#include "contenedorTextura.hpp"
//TODO estas constantes estaban definidas para el tuto.
#define SCREEN_WIDTH = 640;
#define SCREEN_HEIGHT = 480;
#define AVION_ANCHO = 20;
#define AVION_ALTO = 20;
using namespace std;

class Avion{
private:
	string idSprite;
	float velocidadDesplazamiento;
	Disparo disparo;
	string idSpriteAnimacion;
	string idSpriteDisparo;
	float posX;
  float posY;
  float velocidadX;
  float velocidadY;
	SDL_Renderer* gAvionRenderer;
	ContenedorTextura gAvionTextura;

public:
	Avion(string idSprite,int velocidadDesplazamiento,string idSpriteAnimacion, Disparo unDisparo);
	Avion();
	~Avion();
	void setDisparo(Disparo unDisparo);
	Disparo getDisparo();
	string getIdSprite();
	void setIdSprite(string idSprite);
	int getVelocidadDesplazamiento();
	void setVelocidadDesplazamiento(int velocidadDesplazamiento);
	string getIdSpriteAnimacion();
	void setIdSpriteAnimacion(string idSpriteAnimacion);
	void mover(float timeStep);
	void render();
	void disparar();
	float getVelocidadX();
	float getVelocidadY();
	bool cargarImagen();
	void cerrar();
	SDL_Renderer* getAvionRenderer();
	ContenedorTextura getAvionTextura();
};

#endif
