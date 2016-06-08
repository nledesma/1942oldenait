#ifndef BOTONSIGUIENTE_H
#define BOTONSIGUIENTE_H
#include "boton.hpp"

enum LButtonSpriteSiguiente{

	BUTTON_SPRITE_SIGUIENTE_OUT = 0,
	BUTTON_SPRITE_SIGUIENTE_MOTION = 1,
	BUTTON_SPRITE_SIGUIENTE_DOWN = 2,
	BUTTON_SPRITE_TOTAL_SIGUIENTE = 3
};

class BotonSiguiente : public Boton{
	private:
		LButtonSpriteSiguiente mCurrentSprite;
		SDL_Rect gSpriteClips3[BUTTON_SPRITE_TOTAL_SIGUIENTE];
	public:
		BotonSiguiente();
		int handleEvent(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
