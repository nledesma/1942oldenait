#include "elementoVista.hpp"

ElementoVista::ElementoVista(int id, float posX, float posY){
    this->id = id;
    this->posX = posX;
    this->posY = posY;
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

/*
void ElementoVista::render(SDL_Renderer* renderer){
  this->figuraElemento->render((int)this->posX, (int)this->posY, renderer, NULL);
}
*/
