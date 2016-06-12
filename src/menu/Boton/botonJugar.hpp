#ifndef BOTONJUGAR_H
#define BOTONJUGAR_H
#include "boton.hpp"

enum BotonSpriteJugar{

	BUTTON_SPRITE_JUGAR_OUT = 0,
	BUTTON_SPRITE_JUGAR_MOTION = 1,
	BUTTON_SPRITE_JUGAR_DOWN = 2,
	BUTTON_SPRITE_JUGAR_TOTAL = 3
};

class BotonJugar : public Boton{
	private:
		BotonSpriteJugar sprite;
		SDL_Rect spriteBoton[BUTTON_SPRITE_JUGAR_TOTAL];
	public:
		BotonJugar();
		int manejarEvento(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
