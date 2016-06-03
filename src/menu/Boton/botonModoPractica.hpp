#ifndef BOTONMODOPRACTICA_H
#define BOTONMODOPRACTICA_H
#include "boton.hpp"

enum LButtonSpriteModoPractica{

	BUTTON_SPRITE_MODO_PRACTICA_OUT = 0,
	BUTTON_SPRITE_MODO_PRACTICA_MOTION = 1,
	BUTTON_SPRITE_MODO_PRACTICA_DOWN = 2,
	BUTTON_SPRITE_MODO_PRACTICA_TOTAL = 3
};

class BotonModoPractica : public Boton{
	private:
		LButtonSpriteModoPractica mCurrentSprite;
		SDL_Rect gSpriteClips[BUTTON_SPRITE_MODO_PRACTICA_TOTAL];
	public:
		BotonModoPractica();
		int handleEvent(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
