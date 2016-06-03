#include "menu.hpp"
Menu::Menu(){
    this->gFont = NULL;
    this->textTexture = new Figura();
}

Figura* Menu::getFiguraTexto(){
    return this->textTexture;
}

void Menu::cerrar(){
    this->textTexture->free();
    //Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;
	//Destroy window
	//SDL_DestroyRenderer(this->getVentana()->getRenderer());
	//SDL_DestroyWindow(this->getVentana()->getWindow());
	//this->getVentana()->cerrar();
	//Quit SDL subsystems
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
