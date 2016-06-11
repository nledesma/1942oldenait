#include "disparoVista.hpp"

DisparoVista::DisparoVista(string pathSprite){
    this->figuraDisparo = new Figura();
    this->pathSprite = pathSprite;

    //Avión en estado normal
    this->clipsAnimacion[0].x = 0;
    this->clipsAnimacion[0].y = 0;
    this->clipsAnimacion[0].w = ANCHO_DISPARO_COMUN;
    this->clipsAnimacion[0].h = ALTO_DISPARO_COMUN;

    this->clipsAnimacion[1].x = ANCHO_DISPARO_COMUN;
    this->clipsAnimacion[1].y = 0;
    this->clipsAnimacion[1].w = ANCHO_DISPARO_COMUN;
    this->clipsAnimacion[1].h = ALTO_DISPARO_COMUN;
}

DisparoVista::~DisparoVista(){ }

void DisparoVista::cargarImagen(SDL_Renderer * renderer){
    if(!this->figuraDisparo->loadFromFile(this->pathSprite, renderer)){
        this->figuraDisparo->loadFromFile(DISPARO_POR_DEFECTO, renderer);
    }
}

void DisparoVista::render(float posX, float posY, int estado ,SDL_Renderer * renderer){
    this->figuraDisparo->render((int)posX, (int)posY, renderer, &clipsAnimacion[estado]);
}

void DisparoVista::cerrar() {
    this->figuraDisparo->free();
}
