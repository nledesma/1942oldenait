#ifndef BOTONSALIR_H
#define BOTONSALIR_H
#include "boton.hpp"

enum LButtonSpriteSalir{

	BUTTON_SPRITE_SALIR_OUT = 0,
	BUTTON_SPRITE_SALIR_MOTION = 1,
	BUTTON_SPRITE_SALIR_DOWN = 2,
	BUTTON_SPRITE_TOTAL_SALIR = 3
};

class BotonSalir : public Boton{
	private:
		LButtonSpriteSalir mCurrentSprite;
		SDL_Rect gSpriteClips3[BUTTON_SPRITE_TOTAL_SALIR];
	public:
		BotonSalir();
		int handleEvent( SDL_Event* e );
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
