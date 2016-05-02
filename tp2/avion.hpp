#ifndef AVION_HPP
#define AVION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include "disparo.hpp"
#include "figura.hpp"

//TODO estas constantes estaban definidas para el tuto.
#define SCREEN_WIDTH = 640;
#define SCREEN_HEIGHT = 480;
//#define AVION_ANCHO = 20;
//#define AVION_ALTO = 20;
using namespace std;

class Avion{
private:
	string idSprite;
	string idSpriteVuelta;
	float velocidadDesplazamiento;
	float velocidadDisparos;
	list<Disparo*> disparos;
	string idSpriteAnimacion;
	string idSpriteDisparo;
	float posX;
  float posY;
  float velocidadX;
  float velocidadY;
	SDL_Rect clipsAnimacion[3];
	int estadoAnimacion;
	SDL_Renderer* gAvionRenderer;
	Figura* gAvionTextura;
	float velocidad;

public:
	static const int AVION_ANCHO = 80;
	static const int AVION_ALTO= 80;
	Avion(float velocidadDesplazamiento, float velocidadDisparos, string avionSpriteId, string vueltaSpriteId, string disparosSpriteId);
	~Avion();
	void setDisparos(list<Disparo*> unosDisparos);
	list<Disparo*> getDisparos();
	string getIdSprite();
	void setIdSprite(string idSprite);
	int getVelocidadDesplazamiento();
	void setVelocidadDesplazamiento(int velocidadDesplazamiento);
	string getIdSpriteAnimacion();
	void setIdSpriteAnimacion(string idSpriteAnimacion);
	void render();
	void disparar();
	int getVelocidadX();
	int getVelocidadY();
	float getPosicionX();
	float getPosicionY();
	int cargarImagen(string path, SDL_Renderer* renderer);
	void cerrar();
	SDL_Renderer* getAvionRenderer();
	Figura* getAvionTextura();
	void manejarEvento(SDL_Event evento, SDL_Renderer * renderer);
	void mover(float timeStep);
	void render(SDL_Renderer* renderer);
	void renderDisparos(SDL_Renderer * renderer);
	void moverDisparos(float timeStep);
	int getAncho();
	int getAlto();
};

#endif
