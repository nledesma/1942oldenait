#include "powerUp.hpp"

PowerUp::~PowerUp(){ 

}

/*
void PowerUp::aplicarPowerUp(){}

int PowerUp::getEstadoAnimacion(){
    return this->estadoAnimacion;
}
*/

int PowerUp::getTipoPowerUp() {
    return this->tipo;
}

/*
float PowerUp::getPosicionX(){
    return this->posX;;
}

float PowerUp::getPosicionY(){
    return this->posY;
  }

string PowerUp::getIdSprite(){
      return this->idSprite;
  }
*/

void PowerUp::mover(float timeStep, float velocidadY){
    this->posY += velocidadY * timeStep;
}


void PowerUp::volverEstadoInicial(){
    this->posX = posXInicial;
    this->posY = posYInicial;
}