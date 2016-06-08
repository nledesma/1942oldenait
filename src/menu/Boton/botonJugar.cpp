#include "botonJugar.hpp"
BotonJugar::BotonJugar(){
	this->mCurrentSprite = BUTTON_SPRITE_JUGAR_OUT;
}

int BotonJugar::handleEvent(SDL_Event* e){
	//If mouse event happened
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
			mCurrentSprite = BUTTON_SPRITE_JUGAR_OUT;
		}
		//Mouse is inside button
		else{
			//Set mouse over sprite
			switch( e->type ){
				case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_JUGAR_MOTION;
				return 0;
				break;

				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_JUGAR_DOWN;
				cout << "HOLA ESTOY EN JUGAR" << endl;
				return 1;
				break;
			}
		}
	}
	return -1;
}

void BotonJugar::render(SDL_Renderer* renderer){
	this->getFigura()->renderMenu(renderer, this->getPosicionX(), this->getPosicionY(), &gSpriteClips[ mCurrentSprite ], 0, NULL, (SDL_RendererFlip)NULL);

}

void BotonJugar::setSprites(SDL_Renderer* renderer){
	//Set sprites
	for( int i = 0; i < 3; ++i ){
		gSpriteClips[ i ].x = 0;
		gSpriteClips[ i ].y = i * 48;
		gSpriteClips[ i ].w = BUTTON_WIDTH;
		gSpriteClips[ i ].h = BUTTON_HEIGHT;
	}

}
