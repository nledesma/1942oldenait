#include "avionEnemigo.hpp"

AvionEnemigo::AvionEnemigo(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, string idSprite, string idSpriteDisparos){
    this->posX = posX;
    this->posY = posY;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->velocidadX = 0;
    this->velocidadY = 0;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = ESTADO_NORMAL;
    this->idSprite = idSprite;
    this->idSpriteDisparos = idSpriteDisparos;
}

AvionEnemigo::~AvionEnemigo(){

}

float AvionEnemigo::getVelocidad(){
    return this->velocidad;
}

float AvionEnemigo::getPosicionX(){
    pthread_mutex_lock(&this->mutexMover);
    float posicionX = this->posX;
    pthread_mutex_unlock(&this->mutexMover);
    return posicionX;
}

float AvionEnemigo::getPosicionY(){
    pthread_mutex_lock(&this->mutexMover);
    float posicionY = this->posY;
    pthread_mutex_unlock(&this->mutexMover);
    return posicionY;
  }

string Avion::getIdSprite(){
      return this->idSprite;
  }

string Avion::getIdSpriteDisparos() {
      return this->idSpriteDisparos;
  }
