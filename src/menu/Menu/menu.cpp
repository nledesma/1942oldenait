#include "menu.hpp"

Menu::Menu(Ventana * ventana) {
    this->ventana = ventana;
    this->gFont = NULL;
    this->fondo = new Figura();

    if(!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")){
        cout << "No se ha podido cargar la imagen de fondo." << endl;
    }
}

bool Menu::esTecla(SDL_Event * e, SDL_Keycode tecla) {
    return (e->type == SDL_KEYDOWN) && (e->key.keysym.sym == tecla);
}

bool Menu::esSalida(SDL_Event * e) {
    return ((e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_CLOSE));
}

Menu * Menu::getAnterior() {
    return anterior;
}

Menu * Menu::getSiguiente() {
    return siguiente;
}

void Menu::render() {
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
}

void Menu::cerrar() {
    // Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
