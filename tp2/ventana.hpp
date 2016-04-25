#ifndef VENTANA_HPP
#define VENTANA_HPP

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "contenedorTextura.hpp"
#include "escenario.hpp"

using namespace std;
struct Elemento{
	int posX;
	int posY;
	string idSprite;
};

class Ventana{
	private:
		string idSpriteFondo;
		int ancho;
		int alto;
		list <Elemento> elementos;
		//Interfaz
		SDL_Window* window = NULL;
		SDL_Surface* screenSurface = NULL;
		SDL_Surface* imagenFondo = NULL;
		SDL_Renderer* gVentanaRenderer = NULL;
		ContenedorTextura gTexturaVentana;

	public:
		Ventana(int ancho, int alto);
		void cerrar();
		/* Se retorna 1 en caso de éxito, 0 en caso de error */
		int iniciar();
		bool iniciarElementos();
		string getIdSpriteFondo();
		void setIdSpriteFondo(string id);
		int getAncho();
		void setAncho(int ancho);
		int getAlto();
		void setAlto(int alto);
		list <Elemento> getElementos();
		void agregarElemento(Elemento elemento);
		SDL_Renderer* getVentanaRenderer();
		ContenedorTextura getVentanaTextura();
		SDL_Renderer* getRenderer();
};

#endif
