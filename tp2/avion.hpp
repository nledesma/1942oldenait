#ifndef AVION_HPP
#define AVION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "disparo.hpp"
#include "figura.hpp"

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
	int posX;
  int posY;
  float velocidadX;
  float velocidadY;
	SDL_Renderer* gAvionRenderer;
	Figura* gAvionTextura;
	float velocidad;

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
	int getVelocidadX();
	int getVelocidadY();
	int cargarImagen(string path, SDL_Renderer* renderer);
	void cerrar();
	SDL_Renderer* getAvionRenderer();
	Figura* getAvionTextura();
	void manejarEvento(SDL_Event evento);
	void mover();
	void render(SDL_Renderer* renderer);
};

#endif
