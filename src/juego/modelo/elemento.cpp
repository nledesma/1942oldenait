#include "elemento.hpp"

Elemento::Elemento(int id, float posX, float posY, float velocidadY){
    this->id = id;
    this->posX = posX;
    this->posY = posY;
    this->velocidadY = velocidadY;
}

void Elemento::mover(float timeStep){
    this->posY += this->velocidadY * timeStep;
}

float Elemento::getPosX(){
    return this->posX;
}

float Elemento::getPosY(){
    return this->posY;
}

float Elemento::getVelocidadY() {
    return this->velocidadY;
}

int Elemento::getId(){
    return this->id;
}
