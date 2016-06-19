#ifndef BOTON_H
#define BOTON_H
#include "../../juego/vista/figura.hpp"

#define BOTON_APRETADO 1

enum BotonSprite{

	BUTTON_SPRITE_OUT = 0,
	BUTTON_SPRITE_MOTION = 1,
	BUTTON_SPRITE_DOWN = 2,
	BUTTON_SPRITE_TOTAL = 3
};

class Boton{
    private:
		SDL_Point posicion;
		Figura* figuraBoton;
        BotonSprite sprite;
        SDL_Rect spriteBoton[BUTTON_SPRITE_TOTAL];

	public:
		const int BUTTON_WIDTH = 188;
		const int BUTTON_HEIGHT = 42;
		const int TOTAL_BUTTONS = 1;
		Boton();
        int manejarEvento(SDL_Event* e);
	    void render(SDL_Renderer* renderer);
	    void setSprites(SDL_Renderer* renderer);
		int getPosicionX();
		int getPosicionY();
		void setPosition(int x, int y);
		Figura* getFigura();
};

#endif
