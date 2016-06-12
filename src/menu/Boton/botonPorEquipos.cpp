#include "botonPorEquipos.hpp"
BotonPorEquipos::BotonPorEquipos(){
	this->sprite = BUTTON_SPRITE_POREQUIPOS_OUT;
}

int BotonPorEquipos::manejarEvento(SDL_Event* e){
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		//Check if mouse is in button
		bool inside = true;
		//Mouse is left of the button
		if(x < this->getPosicionX()){
			inside = false;
		}
		//Mouse is right of the button
		else if( x > this->getPosicionX() + BUTTON_WIDTH ){
			inside = false;
		}
		//Mouse above the button
		else if(y < this->getPosicionY()){
			inside = false;
		}
		//Mouse below the button
		else if( y > this->getPosicionY() + BUTTON_HEIGHT ){
			inside = false;
		}
		//Mouse is outside button
		if( !inside ){
			sprite = BUTTON_SPRITE_POREQUIPOS_OUT;
		}
		//Mouse is inside button
		else{
			//Set mouse over sprite
			switch( e->type ){
				case SDL_MOUSEMOTION:
				sprite = BUTTON_SPRITE_POREQUIPOS_MOTION;
				break;

				case SDL_MOUSEBUTTONDOWN:
				sprite = BUTTON_SPRITE_POREQUIPOS_DOWN;
				break;
			}
		}
	}
	return -1;
}

void BotonPorEquipos::render(SDL_Renderer* renderer){
	this->getFigura()->renderMenu(renderer, this->getPosicionX(), this->getPosicionY(), &spriteBoton[sprite],0, NULL, (SDL_RendererFlip)NULL);

}

void BotonPorEquipos::setSprites(SDL_Renderer* renderer){
	for( int i = 0; i < 3; ++i ){
		spriteBoton[i].x = 0;
		spriteBoton[i].y = i * 48;
		spriteBoton[i].w = BUTTON_WIDTH;
		spriteBoton[i].h = BUTTON_HEIGHT;
	}
}
