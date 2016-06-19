#include "enemigoVista.hpp"

void EnemigoVista::cargarImagen(SDL_Renderer * renderer){
    this->figuraEnemigo->loadFromFile(this->pathSprite, renderer);
}

void EnemigoVista::render(float posX, float posY, int estadoAnimacion, SDL_Renderer* renderer){
    this->estadoAnimacion = estadoAnimacion;
    this->figuraEnemigo->render((int)posX, (int)posY, renderer, &clipsAnimacion[estadoAnimacion]);
}

void EnemigoVista::cerrar() {
    this->figuraEnemigo->free();
}