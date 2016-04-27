#ifndef VENTANA_HPP
#define VENTANA_HPP

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "figura.hpp"

using namespace std;

class Ventana{
	private:
		int ancho;
		int alto;
		SDL_Window* sdlWindow = NULL;
		SDL_Renderer* gVentanaRenderer = NULL;

	public:
		Ventana(int ancho, int alto);
		int iniciar();
		void cerrar();
		int getAncho();
		void setAncho(int ancho);
		int getAlto();
		void setAlto(int alto);
		SDL_Renderer* getVentanaRenderer();
		SDL_Window* getSdlWindow();
};

#endif
