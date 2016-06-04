#include "punto.hpp"

Punto::Punto(float posX, float posY) {
    this->posX = posX;
    this->posY = posY;
}

void Punto::setPosX(float posX) {
    this->posX = posX;
}

float Punto::getPosX() {
    return this->posX;
}

void Punto::setPosY(float posY) {
    this->posY = posY;
}

float Punto::getPosY(){
    return this->posY;
}

float Punto::productoPunto(Punto * punto){
    return (this->posX * punto->getPosX() + this->posY * punto->getPosY());
}

void Punto::mover(float x, float y){
    this->posX = x;
    this->posY = y;
}

void Punto::rotar(float angulo, float x, float y){
    float xOriginal = this->posX;
    float yOriginal = this->posY;
    // cout << "Coseno " << Trigonomaster::getCoseno(angulo) << endl;
    // cout << "Seno " << Trigonomaster::getSeno(angulo) << endl;
    // cout << "xOriginal - x " << (xOriginal - x) << endl;
    // cout << "yOriginal - y " << (yOriginal - y) << endl;
    this->posX = Trigonomaster::getCoseno(angulo) * (xOriginal - x) - Trigonomaster::getSeno(angulo) * (yOriginal - y) + x;
    this->posY = Trigonomaster::getSeno(angulo) * (xOriginal - x) + Trigonomaster::getCoseno(angulo) * (yOriginal - y) + y;
}
