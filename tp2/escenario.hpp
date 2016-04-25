#ifndef ESCENARIO_HPP
#define ESCENARIO_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "avion.hpp"
#include "contenedorTextura.hpp"
#include <list>
using namespace std;

struct fondo{
	string idSpriteFondo;
	int ancho;
	int alto;
};

class Escenario{
	private:
		int ancho;
		int alto;
		list<Avion*> aviones;
		ContenedorTextura* gTexturaEscenario;
		string path;
		SDL_Surface* imagenFondo = NULL;

	public:
		Escenario(int ancho, int alto);
		~Escenario();
		bool cargarImagenDeFondo(SDL_Renderer* renderer);
		SDL_Surface* getImagenFondo();
		bool iniciar(SDL_Renderer* renderer, string path);
		int getAncho();
		int getAlto();
		list<Avion*> getAviones();
		void agregarAvion(Avion* avion);
};

#endif
