#ifndef BOTONATRAS_H
#define BOTONATRAS_H
#include "boton.hpp"

enum BotonSpriteAtras{

	BUTTON_SPRITE_ATRAS_OUT = 0,
	BUTTON_SPRITE_ATRAS_MOTION = 1,
	BUTTON_SPRITE_ATRAS_DOWN = 2,
	BUTTON_SPRITE_TOTAL_ATRAS = 3
};

class BotonAtras : public Boton{
	private:
		BotonSpriteAtras sprite;
		SDL_Rect spriteBoton[BUTTON_SPRITE_TOTAL_ATRAS];
	public:
		BotonAtras();
		int manejarEvento(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
