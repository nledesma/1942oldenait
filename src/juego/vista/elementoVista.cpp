#include "elementoVista.hpp"


ElementoVista::ElementoVista(float posX, float posY, string pathSprite){
    this->posX = posX;
    this->posY = posY;
    this->pathSprite = pathSprite;
    this->figura = new Figura();
}

ElementoVista::ElementoVista(string codigo){
    posX = Decodificador::popFloat(codigo);
    posY = Decodificador::popFloat(codigo);
    pathSprite = Decodificador::popIdImg(codigo);
    figura = new Figura();
}

void ElementoVista::actualizar(string codigo){
    pthread_mutex_lock(&mutexActualizar);
    posX = Decodificador::popFloat(codigo);
    posY = Decodificador::popFloat(codigo);
    pthread_mutex_unlock(&mutexActualizar);
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
    pthread_mutex_lock(&mutexActualizar);
    this->figura->render((int)this->posX, (int)this->posY, renderer, NULL);
    pthread_mutex_unlock(&mutexActualizar);
}
