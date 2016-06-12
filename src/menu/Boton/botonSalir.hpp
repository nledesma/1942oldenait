#ifndef BOTONSALIR_H
#define BOTONSALIR_H
#include "boton.hpp"

enum BotonSpriteSalir{

	BUTTON_SPRITE_SALIR_OUT = 0,
	BUTTON_SPRITE_SALIR_MOTION = 1,
	BUTTON_SPRITE_SALIR_DOWN = 2,
	BUTTON_SPRITE_TOTAL_SALIR = 3
};

class BotonSalir : public Boton{
	private:
		BotonSpriteSalir sprite;
		SDL_Rect spriteBoton[BUTTON_SPRITE_TOTAL_SALIR];
	public:
		BotonSalir();
		int manejarEvento(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
