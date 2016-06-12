#ifndef BOTONPOREQUIPOS_H
#define BOTONPOREQUIPOS_H
#include "boton.hpp"

enum BotonSpritePorEquipos{

	BUTTON_SPRITE_POREQUIPOS_OUT = 0,
	BUTTON_SPRITE_POREQUIPOS_MOTION = 1,
	BUTTON_SPRITE_POREQUIPOS_DOWN = 2,
	BUTTON_SPRITE_TOTAL_POREQUIPOS = 3
};

class BotonPorEquipos : public Boton{
	private:
		BotonSpritePorEquipos sprite;
		SDL_Rect spriteBoton[BUTTON_SPRITE_TOTAL_POREQUIPOS];
	public:
		BotonPorEquipos();
		int manejarEvento(SDL_Event* e);
		void render(SDL_Renderer* renderer);
		void setSprites(SDL_Renderer* renderer);
};

#endif
