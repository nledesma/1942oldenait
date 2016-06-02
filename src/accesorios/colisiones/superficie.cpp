#include "superficie.hpp"

Superficie::Superficie(float x, float y, int ancho, int alto){
    this->izqAbajo[0] = x;
    this->izqAbajo[1] = y;

    this->izqArriba[0] = x;
    this->izqArriba[1] = y + alto;

    this->derArriba[0] = x + ancho;
    this->derArriba[1] = y + alto;

    this->derAbajo[0] = x + ancho;
    this->derAbajo[1] = y;

    this->rotar(angulo);
}

float[2] Superficie::getIzqAbajo(){
    return this->izqAbajo;
}

float[2] Superficie::getIzqArriba(){
    return this->izqArriba;
}

float[2] Superficie::getDerArriba(){
    return this->derArriba;
}

float[2] Superficie::getDerAbajo(){
    return this->derAbajo;
}

void Superficie::rotar(float angulo, float x, float y){

    float xOriginal = this->izqAbajo[0];
    float yOriginal = this->izqArriba[1];
    this->izqAbajo[0] = Trigonomaster::getCoseno(angulo) * (xOriginal - x) - Trigonomaster::getSeno(angulo) * (yOriginal - y) + x;
    this->izqAbajo[1] = Trigonomaster::getSeno(angulo) * (xOriginal - x) + Trigonomaster::getCoseno(angulo) * (yOriginal - y) + y;

    xOriginal = this->izqArriba[0];
    yOriginal = this->izqAbajo[1];
    this->izqArriba[0] = Trigonomaster::getCoseno(angulo) * (xOriginal - x) - Trigonomaster::getSeno(angulo) * (yOriginal - y) + x;
    this->izqArriba[1] = Trigonomaster::getSeno(angulo) * (xOriginal - x) + Trigonomaster::getCoseno(angulo) * (yOriginal - y) + y;

    xOriginal = this->derArriba[0];
    yOriginal = this->derArriba[1];
    this->derArriba[0] = Trigonomaster::getCoseno(angulo) * (xOriginal - x) - Trigonomaster::getSeno(angulo) * (yOriginal - y) + x;
    this->derArriba[1] = Trigonomaster::getSeno(angulo) * (xOriginal - x) + Trigonomaster::getCoseno(angulo) * (yOriginal - y) + y;

    xOriginal = this->derAbajo[0];
    yOriginal = this->derAbajo[1];
    this->derAbajo[0] = Trigonomaster::getCoseno(angulo) * (xOriginal - x) - Trigonomaster::getSeno(angulo) * (yOriginal - y) + x;
    this->derAbajo[1] = Trigonomaster::getSeno(angulo) * (xOriginal - x) + Trigonomaster::getCoseno(angulo) * (yOriginal - y) + y;
}

bool Superficie::colisiona(Superficie * superficie){

}
