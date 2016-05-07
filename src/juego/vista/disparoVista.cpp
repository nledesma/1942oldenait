#include "disparoVista.hpp"

#include "disparoVista.hpp"

DisparoVista::DisparoVista(string pathSprite){
    this->figuraDisparo = new Figura();
    this->pathSprite = pathSprite;
}

DisparoVista::~DisparoVista(){ }

int DisparoVista::cargarImagen(SDL_Renderer * renderer){
    if(!this->figuraDisparo->loadFromFile(this->pathSprite, renderer)){
        this->figuraDisparo->loadFromFile(DisparoVista::DISPARO_POR_DEFECTO, renderer);
    }
}

void DisparoVista::render(float posX, float posY, SDL_Renderer * renderer){
    this->figuraDisparo->render((int)posX, (int)posY, renderer, NULL);
}