#ifndef BOTON_H
#define BOTON_H
#include "../../juego/vista/figura.hpp"

#define BOTON_APRETADO 1
class Boton{
	protected:
		SDL_Point posicion;
		Figura* figuraBoton;
		virtual int manejarEvento(SDL_Event* e) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		virtual void setSprites(SDL_Renderer* renderer) = 0;
	public:
		const int BUTTON_WIDTH = 188;
		const int BUTTON_HEIGHT = 42;
		const int TOTAL_BUTTONS = 1;
		Boton();
		int getPosicionX();
		int getPosicionY();
		void setPosition(int x, int y);
		Figura* getFigura();
};

#endif
