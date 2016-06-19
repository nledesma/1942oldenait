#include "boton.hpp"
Boton::Boton(){
	this->posicion.x = 0;
	this->posicion.y = 0;
	this->figuraBoton = new Figura();
    this->sprite = BUTTON_SPRITE_OUT;
}

int Boton::getPosicionX(){
	return this->posicion.x;
}

int Boton::getPosicionY(){
	return this->posicion.y;
}

void Boton::setPosition(int x, int y){
	posicion.x = x;
	posicion.y = y;
}

Figura* Boton::getFigura(){
	return this->figuraBoton;
}

int Boton::manejarEvento(SDL_Event* e){
	// cout << "ENTRO AL MANEJAR EVENTO DE BOTON GENERAL" << endl;
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
			sprite = BUTTON_SPRITE_OUT;
		}else{
			switch(e->type){
				case SDL_MOUSEMOTION:
				sprite = BUTTON_SPRITE_MOTION;
				return 0;
				break;

				case SDL_MOUSEBUTTONDOWN:
				sprite = BUTTON_SPRITE_DOWN;
				return BOTON_APRETADO;
				break;
			}
		}
	}
	return -1;
}

void Boton::render(SDL_Renderer* renderer){
	this->getFigura()->renderMenu(renderer, this->getPosicionX(), this->getPosicionY(), &spriteBoton[sprite], 0, NULL, (SDL_RendererFlip)NULL);

}

void Boton::setSprites(SDL_Renderer* renderer){
	this->spriteBoton[BUTTON_SPRITE_OUT].x = 0;
	this->spriteBoton[BUTTON_SPRITE_OUT].y = 0;
	this->spriteBoton[BUTTON_SPRITE_OUT].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_OUT].h = BUTTON_HEIGHT;

	this->spriteBoton[BUTTON_SPRITE_MOTION].x = 0;
	this->spriteBoton[BUTTON_SPRITE_MOTION].y = 48;
	this->spriteBoton[BUTTON_SPRITE_MOTION].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_MOTION].h = BUTTON_HEIGHT;

	this->spriteBoton[BUTTON_SPRITE_DOWN].x = 0;
	this->spriteBoton[BUTTON_SPRITE_DOWN].y = 2 * 48;
	this->spriteBoton[BUTTON_SPRITE_DOWN].w = BUTTON_WIDTH;
	this->spriteBoton[BUTTON_SPRITE_DOWN].h = BUTTON_HEIGHT;
}
