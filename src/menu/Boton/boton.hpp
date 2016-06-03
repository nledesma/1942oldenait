#ifndef BOTON_H
#define BOTON_H
#include "../../juego/vista/figura.hpp"

class Boton{
	protected:
		SDL_Point mPosition;
		Figura* gButtonSpriteSheetTexture;
		virtual int handleEvent(SDL_Event* e) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		virtual void setSprites(SDL_Renderer* renderer) = 0;
	public:
		const int BUTTON_WIDTH = 193;
		const int BUTTON_HEIGHT = 48;
		const int TOTAL_BUTTONS = 1;
		Boton();
		int getPosicionX();
		int getPosicionY();
		//Sets top left position
		void setPosition(int x, int y);
		Figura* getFigura();
};

#endif
