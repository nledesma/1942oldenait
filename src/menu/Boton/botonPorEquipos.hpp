#ifndef BOTONPOREQUIPOS_H
#define BOTONPOREQUIPOS_H
#include "boton.hpp"

enum LButtonSpritePorEquipos{

	BUTTON_SPRITE_POREQUIPOS_OUT = 0,
	BUTTON_SPRITE_POREQUIPOS_MOTION = 1,
	BUTTON_SPRITE_POREQUIPOS_DOWN = 2,
	BUTTON_SPRITE_TOTAL_POREQUIPOS = 3
};

class BotonPorEquipos : public Boton{
	private:
		LButtonSpritePorEquipos mCurrentSprite;
		SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL_POREQUIPOS];
	public:
		BotonPorEquipos();
		int handleEvent(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
