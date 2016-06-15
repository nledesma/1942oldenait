#include "botonSiguiente.hpp"

BotonSiguiente::BotonSiguiente(){
	this->sprite = BUTTON_SPRITE_SIGUIENTE_OUT;
}

int BotonSiguiente::manejarEvento(SDL_Event* e){
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if(x < this->getPosicionX()){
			inside = false;
		}else if( x > this->getPosicionX() + BUTTON_WIDTH){
			inside = false;
		}else if(y < this->getPosicionY()){
			inside = false;
		}else if( y > this->getPosicionY() + BUTTON_HEIGHT){
			inside = false;
		}
		if(!inside){
			sprite = BUTTON_SPRITE_SIGUIENTE_OUT;
		}else{
			switch(e->type){
				case SDL_MOUSEMOTION:
				sprite = BUTTON_SPRITE_SIGUIENTE_MOTION;
				return 0;
				break;

				case SDL_MOUSEBUTTONDOWN:
				sprite = BUTTON_SPRITE_SIGUIENTE_DOWN;
				return BOTON_APRETADO;
				break;
			}
		}
	}
	return -1;
}

void BotonSiguiente::render(SDL_Renderer* renderer){
	this->getFigura()->renderMenu(renderer, this->getPosicionX(), this->getPosicionY(), &spriteBoton[sprite],0, NULL, (SDL_RendererFlip)NULL);

}

void BotonSiguiente::setSprites(SDL_Renderer* renderer){
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_OUT].x = 0;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_OUT].y = 0;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_OUT].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_OUT].h = BUTTON_HEIGHT;

	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_MOTION].x = 0;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_MOTION].y = 48;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_MOTION].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_MOTION].h = BUTTON_HEIGHT;

	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_DOWN].x = 0;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_DOWN].y = 2 * 48;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_DOWN].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_SIGUIENTE_DOWN].h = BUTTON_HEIGHT;
}
