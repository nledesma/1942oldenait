#include "powerUp.hpp"

PowerUp::~PowerUp(){

}


void PowerUp::aplicarPowerUp(){}

Colisionable* PowerUp::getColisionable(){
    return this->colisionable;
}

void PowerUp::colisionar(){
    if(this->estadoAnimacion < POWER_UP_COLISIONADO){
        this->tiempoPowerUpColisionado = 3000;
        this->estadoAnimacion = POWER_UP_COLISIONADO;
	}
}

int PowerUp::getEstadoAnimacion(){
    pthread_mutex_lock(&this->mutexMover);
    int estadoAnimacion =  this->estadoAnimacion;
    pthread_mutex_unlock(&this->mutexMover);
    return estadoAnimacion;
}

int PowerUp::getTipoPowerUp() {
    pthread_mutex_lock(&this->mutexMover);
    int tipo=  this->tipo;
    pthread_mutex_unlock(&this->mutexMover);
    return tipo;
}

float PowerUp::getPosicionX(){
    pthread_mutex_lock(&this->mutexMover);
    float posX = this->posX;
    pthread_mutex_unlock(&this->mutexMover);
    return posX;
}

float PowerUp::getPosicionY(){
    pthread_mutex_lock(&this->mutexMover);
    float posY = this->posY;
    pthread_mutex_unlock(&this->mutexMover);
    return posY;
}

int PowerUp::getValor(){
    pthread_mutex_lock(&this->mutexMover);
    int valor =  this->valor;
    pthread_mutex_unlock(&this->mutexMover);
    return valor;
}

string PowerUp::getIdSprite(){
      return this->idSprite;
  }

int PowerUp::mover(float timeStep, float velocidadY){
    int resultado = 0;
    pthread_mutex_lock(&this->mutexMover);
    this->posY += velocidadY * timeStep;
    if(this->animar(timeStep)){
        this->colisionable->mover(this->posX, this->posY, 0, TIPO_POWERUP);
        resultado = 1;
    }
    pthread_mutex_unlock(&this->mutexMover);
    return resultado;
}

bool PowerUp::animar(float timeStep){
    if (this->estadoAnimacion != POWER_UP_COLISIONADO) {
        if ((this->contadorTiempoAnimacion + timeStep) >= FRECUENCIA_ANIMACION) {
            this->contadorTiempoAnimacion = 0;
            if (this->estadoAnimacion < POWER_UP_ROTACION_6){
                this->estadoAnimacion += 1;
                return true;
            }
            else {
                this->estadoAnimacion = POWER_UP_NORMAL;
                return true;
            }
        } else {
            this->contadorTiempoAnimacion += timeStep;
            return true;
        }
    } else {
        if(this->tiempoPowerUpColisionado > 0){
            this->tiempoPowerUpColisionado -= this->tiempoPowerUpColisionado * timeStep;
            return true;
        } else {
            return false;
        }
    }
}


void PowerUp::volverEstadoInicial(){
    this->posX = posXInicial;
    this->posY = posYInicial;
    this->colisionable->mover(this->posX, this->posY, 0, TIPO_POWERUP);
    this->estadoAnimacion = POWER_UP_NORMAL;
}
