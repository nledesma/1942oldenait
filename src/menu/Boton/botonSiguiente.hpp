#ifndef BOTONSIGUIENTE_H
#define BOTONSIGUIENTE_H
#include "boton.hpp"

enum BotonSpriteSiguiente{

	BUTTON_SPRITE_SIGUIENTE_OUT = 0,
	BUTTON_SPRITE_SIGUIENTE_MOTION = 1,
	BUTTON_SPRITE_SIGUIENTE_DOWN = 2,
	BUTTON_SPRITE_TOTAL_SIGUIENTE = 3
};

class BotonSiguiente : public Boton{
	private:
		BotonSpriteSiguiente sprite;
		SDL_Rect spriteBoton[BUTTON_SPRITE_TOTAL_SIGUIENTE];
	public:
		BotonSiguiente();
		int manejarEvento(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
