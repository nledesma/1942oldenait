#include "disparoEnemigoVista.hpp"

DisparoEnemigoVista::DisparoEnemigoVista(){
    this->figuraDisparo = new Figura();
    this->pathSprite = SPRITE_DISPARO_ENEMIGO;
}

DisparoEnemigoVista::~DisparoEnemigoVista(){ }

void DisparoEnemigoVista::cargarImagen(SDL_Renderer * renderer){
    if(!this->figuraDisparo->loadFromFile(this->pathSprite, renderer)){
        this->figuraDisparo->loadFromFile(DISPARO_POR_DEFECTO, renderer);
    }
}

void DisparoEnemigoVista::render(float posX, float posY, SDL_Renderer * renderer){
    this->figuraDisparo->render((int)posX, (int)posY, renderer, NULL);
}

void DisparoEnemigoVista::cerrar() {
    this->figuraDisparo->free();
}

