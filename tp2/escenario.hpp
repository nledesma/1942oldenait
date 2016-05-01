#ifndef ESCENARIO_HPP
#define ESCENARIO_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "ventana.hpp"
#include "avion.hpp"
#include "figura.hpp"
#include "temporizador.hpp"
#include "elemento.hpp"
#include <list>
#include <iterator>

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
		list<Elemento*> elementos;
		Figura* fondoEscenario;
		string path;

	public:
		const int LEVEL_WIDTH = 1280;
		const int LEVEL_HEIGHT = 960;
		Escenario(int ancho, int alto);
		~Escenario();
		bool cargarImagenDeFondo(SDL_Renderer* renderer);
		void cargarAvion(Avion* avion, SDL_Renderer* renderer, string path);
		void cargarElemento(Elemento* elemento, SDL_Renderer* renderer, string path);
		int iniciar(string path);
		int getAncho();
		int getAlto();
		bool cargarImagenes(string path);
		//Ventana* getVentana();
		list<Avion*>& getAviones();
		list<Elemento*>& getElementos();
		void agregarAvion(float velocidadDesplazamiento, float velocidadDisparos, string avionSpriteId, string vueltaSpriteId, string disparosSpriteId);
		void agregarElemento(string spriteId, float posX, float posY);
		Figura* getFondoEscenario();
		Avion* getAvion();
		void iniciarCamara(Avion* avion);
		Ventana* getVentana();
		const char* getFondoSprite();
		int getAnchoFondo();
		int getAltoFondo();
		void incluirAviones();
		void incluirElementos();
		void renderizarAviones(SDL_Renderer* renderer);
		void renderizarElementos(SDL_Renderer* renderer);
};

#endif
