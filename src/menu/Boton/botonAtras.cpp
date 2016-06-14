#include "botonAtras.hpp"

BotonAtras::BotonAtras(){
	this->sprite = BUTTON_SPRITE_ATRAS_OUT;
}

int BotonAtras::manejarEvento(SDL_Event* e){
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
			sprite = BUTTON_SPRITE_ATRAS_OUT;
		}else{
			switch(e->type){
				case SDL_MOUSEMOTION:
				sprite = BUTTON_SPRITE_ATRAS_MOTION;
				return 0;
				break;

				case SDL_MOUSEBUTTONDOWN:
				sprite = BUTTON_SPRITE_ATRAS_DOWN;
				return BOTON_APRETADO;
				break;
			}
		}
	}
	return -1;
}

void BotonAtras::render(SDL_Renderer* renderer){
	this->getFigura()->renderMenu(renderer, this->getPosicionX(), this->getPosicionY(), &spriteBoton[sprite],0, NULL, (SDL_RendererFlip)NULL);

}

void BotonAtras::setSprites(SDL_Renderer* renderer){
	for( int i = 0; i < 3; ++i ){
		spriteBoton[i].x = 0;
		spriteBoton[i].y = i * 48;
		spriteBoton[i].w = BUTTON_WIDTH;
		spriteBoton[i].h = BUTTON_HEIGHT;
	}
}
