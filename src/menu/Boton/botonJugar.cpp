#include "botonJugar.hpp"
BotonJugar::BotonJugar(){
	this->sprite = BUTTON_SPRITE_JUGAR_OUT;
}

int BotonJugar::manejarEvento(SDL_Event* e){
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
		if( !inside ){
			sprite = BUTTON_SPRITE_JUGAR_OUT;
		}else{
			switch(e->type){
				case SDL_MOUSEMOTION:
				sprite = BUTTON_SPRITE_JUGAR_MOTION;
				return 0;
				break;

				case SDL_MOUSEBUTTONDOWN:
				sprite = BUTTON_SPRITE_JUGAR_DOWN;
				return BOTON_APRETADO;
				break;
			}
		}
	}
	return -1;
}

void BotonJugar::render(SDL_Renderer* renderer){
	this->getFigura()->renderMenu(renderer, this->getPosicionX(), this->getPosicionY(), &spriteBoton[sprite], 0, NULL, (SDL_RendererFlip)NULL);

}

void BotonJugar::setSprites(SDL_Renderer* renderer){
	this->spriteBoton[BUTTON_SPRITE_JUGAR_OUT].x = 0;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_OUT].y = 0;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_OUT].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_OUT].h = BUTTON_HEIGHT;

	this->spriteBoton[BUTTON_SPRITE_JUGAR_MOTION].x = 0;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_MOTION].y = 48;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_MOTION].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_MOTION].h = BUTTON_HEIGHT;

	this->spriteBoton[BUTTON_SPRITE_JUGAR_DOWN].x = 0;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_DOWN].y = 2 * 48;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_DOWN].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_JUGAR_DOWN].h = BUTTON_HEIGHT;
}
