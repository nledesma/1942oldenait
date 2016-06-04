#include "avionEnemigo.hpp"

AvionEnemigo::~AvionEnemigo() { }

float AvionEnemigo::getVelocidad(){
    return this->velocidad;
}

float AvionEnemigo::getAngulo() {
    return this->angulo;
}

int AvionEnemigo::getEstadoAnimacion(){
    pthread_mutex_lock(&this->mutexMover);
    int estado = this->estadoAnimacion;
    pthread_mutex_unlock(&this->mutexMover);
    return estado;
}

int AvionEnemigo::getTipoAvion() {
    return this->tipoAvion;
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

int AvionEnemigo::getAnchoDisparo() {
    return ANCHO_DISPARO_ENEMIGO;
}

int AvionEnemigo::getAltoDisparo() {
    return ALTO_DISPARO_ENEMIGO;
}

int AvionEnemigo::mover(float timeStep) {
    pthread_mutex_lock(&this->mutexMover);
    int sigueEnPantalla = 1;
    this->trayectoria->mover(this->posX, this->posY, this->velocidad, this->angulo, this->estadoAnimacion, timeStep);
    // TODO: chequear los bordes usando los atributos del escenario
    if (this->posX > ANCHO_ESCENARIO || this->posX < - this->getAncho()
        || this->posY > ALTO_ESCENARIO || this->posY < - this->getAlto()){
        sigueEnPantalla = 0;
    }
    pthread_mutex_unlock(&this->mutexMover);
    return sigueEnPantalla;
}