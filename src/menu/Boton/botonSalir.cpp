#include "botonSalir.hpp"
BotonSalir::BotonSalir(){
	this->sprite = BUTTON_SPRITE_SALIR_OUT;
}

int BotonSalir::manejarEvento(SDL_Event* e){
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if(x < this->getPosicionX()){
			inside = false;
		}else if(x > this->getPosicionX() + BUTTON_WIDTH){
			inside = false;
		}else if(y < this->getPosicionY()){
			inside = false;
		}else if(y > this->getPosicionY() + BUTTON_HEIGHT){
			inside = false;
		}
		if(!inside){
			sprite = BUTTON_SPRITE_SALIR_OUT;
		}else{
			switch(e->type){
				case SDL_MOUSEMOTION:
				sprite = BUTTON_SPRITE_SALIR_MOTION;
				return 0;
				break;

				case SDL_MOUSEBUTTONDOWN:
				sprite = BUTTON_SPRITE_SALIR_DOWN;
				return BOTON_APRETADO;
				break;
			}
		}
	}
	return -1;
}

void BotonSalir::render(SDL_Renderer* renderer){
	this->getFigura()->renderMenu(renderer, this->getPosicionX(), this->getPosicionY(), &spriteBoton[sprite], 0, NULL, (SDL_RendererFlip)NULL );

}

void BotonSalir::setSprites(SDL_Renderer* renderer){
	this->spriteBoton[BUTTON_SPRITE_SALIR_OUT].x = 0;
	this->spriteBoton[BUTTON_SPRITE_SALIR_OUT].y = 0;
	this->spriteBoton[BUTTON_SPRITE_SALIR_OUT].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_SALIR_OUT].h = BUTTON_HEIGHT;

	this->spriteBoton[BUTTON_SPRITE_SALIR_MOTION].x = 0;
	this->spriteBoton[BUTTON_SPRITE_SALIR_MOTION].y = 48;
	this->spriteBoton[BUTTON_SPRITE_SALIR_MOTION].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_SALIR_MOTION].h = BUTTON_HEIGHT;

	this->spriteBoton[BUTTON_SPRITE_SALIR_DOWN].x = 0;
	this->spriteBoton[BUTTON_SPRITE_SALIR_DOWN].y = 2 * 48;
	this->spriteBoton[BUTTON_SPRITE_SALIR_DOWN].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_SALIR_DOWN].h = BUTTON_HEIGHT;
}
