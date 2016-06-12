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
	for(int i = 0; i < 3; ++i){
		spriteBoton[i].x = 0;
		spriteBoton[i].y = i * 48;
		spriteBoton[i].w = BUTTON_WIDTH;
		spriteBoton[i].h = BUTTON_HEIGHT;
	}
}
