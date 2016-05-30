#include "colisionable.hpp"

Colisionable::Colisionable(float x, float y, float ancho, float alto){
    this->posX = x;
    this->posY = y;
    this->ancho = ancho;
    this->alto = alto;
    this->angulo = 0;
}

Colisionable::Colisionable(float x, float y, float ancho, float alto, float angulo){
  this->posX = x;
  this->posY = y;
  this->ancho = ancho;
  this->alto = alto;
  this->angulo = angulo;
}

float Colisionable::getPosX(){
    return this->posX;
}

float Colisionable::getPosY(){
    return this->posY;
}

float Colisionable::getAncho(){
    return this->ancho;
}

float Colisionable::getAlto(){
    return this->alto;
}

void Colisionable::setPosX(float posX){
    this->posX = posX;
}

void Colisionable::setPosY(float posY){
    this->posY = posY;
}

void Colisionable::setAngulo(float angulo){
    this->angulo = angulo;
}

float Colisionable::getAngulo(){
    return this->angulo;
}

bool Colisionable::colisiona(Colisionable * colisionable){
    int izquierda, izquierdaColisionable;
    int derecha, derechaColisionable;
    int arriba, arribaColisionable;
    int abajo, abajoColisionable;

    izquierda = this->posX;
    derecha = this->posX + this->ancho;
    arriba = this->posY;
    abajo = this->posY + this->alto;

    izquierdaColisionable = colisionable->getPosX();
    derechaColisionable = colisionable->getPosX() + colisionable->getAncho();
    arribaColisionable = colisionable->getPosY();
    abajoColisionable = colisionable->getPosY() + colisionable->getAlto();


    if((arribaColisionable <= 0) || (abajo <= arribaColisionable)){
            return false;
    }

    if((abajoColisionable <= 0) || (arriba >= abajoColisionable)){
            return false;
    }

    if(derecha <= izquierdaColisionable){
        return false;
    }

    if(izquierda >= derechaColisionable){
        return false;
    }

    return true;
}
