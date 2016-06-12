#ifndef BOTONENCOLABORACION_H
#define BOTONENCOLABORACION_H
#include "boton.hpp"

enum BotonSpriteEnColaboracion{

	BUTTON_SPRITE_ENCOLABORACION_OUT = 0,
	BUTTON_SPRITE_ENCOLABORACION_MOTION = 1,
	BUTTON_SPRITE_ENCOLABORACION_DOWN = 2,
	BUTTON_SPRITE_ENCOLABORACION_TOTAL = 3
};

class BotonEnColaboracion : public Boton{
	private:
		BotonSpriteEnColaboracion sprite;
		SDL_Rect botonSprite[BUTTON_SPRITE_ENCOLABORACION_TOTAL];
	public:
		BotonEnColaboracion();
		int manejarEvento(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
