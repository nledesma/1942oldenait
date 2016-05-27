#include "avionEnemigo.hpp"

float AvionEnemigo::getVelocidad(){
    return this->velocidad;
}

float AvionEnemigo::getAngulo() {
    return this->angulo;
}

int AvionEnemigo::getEstadoAnimacion() {
    
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

string AvionEnemigo::getIdSprite(){
      return this->idSprite;
  }

string AvionEnemigo::getIdSpriteDisparos() {
      return this->idSpriteDisparos;
  }
