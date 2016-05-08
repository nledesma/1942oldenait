#include "elementoVista.hpp"


ElementoVista::ElementoVista(float posX, float posY, string pathSprite){

    this->posX = posX;
    this->posY = posY;
    this->pathSprite = pathSprite;
    this->figura = new Figura();

}

void ElementoVista::actualizar(string codigo){
    memcpy((void*)&(this->posX),(void*)&(codigo[0]), sizeof(float));
    memcpy((void*)&(this->posY),(void*)&(codigo[sizeof(float)]), sizeof(float));
}

float ElementoVista::getPosX(){
    return posX;
}

float ElementoVista::getPosY(){
    return posY;
}

void ElementoVista::cargarImagen(SDL_Renderer* renderer){
    if(!this->figura->loadFromFile(this->pathSprite, renderer)){
        this->figura->loadFromFile((string) ELEMENTO_POR_DEFECTO, renderer);
    }
}

void ElementoVista::render(SDL_Renderer* renderer){
  this->figura->render((int)this->posX, (int)this->posY, renderer, NULL);
}
