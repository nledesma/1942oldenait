#ifndef ESCENARIO_HPP
#define ESCENARIO_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "ventana.hpp"
#include "avion.hpp"
#include "Figura.hpp"
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
		Ventana* ventana;
		list<Avion*> aviones;
		Figura* fondoEscenario;
		string path;

	public:
		Escenario(int ancho, int alto);
		~Escenario();
		bool cargarImagenDeFondo(SDL_Renderer* renderer);
		bool iniciar(SDL_Renderer* renderer, string path);
		int getAncho();
		int getAlto();
		bool cargarImagenes(string path);
		//Ventana* getVentana();
		list<Avion*> getAviones();
		void agregarAvion(Avion* avion);
		SDL_Surface* getImagenFondo();
};

#endif
