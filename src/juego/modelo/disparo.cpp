#include "disparo.hpp"

Disparo::Disparo(float posX, float posY, float velocidad){
    this->posX = posX;
    this->posY = posY;
    this->velocidad = velocidad;
    this->colisionable = new Colisionable(this->posX, this->posY, 0, TIPO_DISPARO_AVION);
    this->colisiono = false;
    this->alturaDeMuerte = -1;
    this->estado = 0;
    this->contadorExplosionImpacto = TIEMPO_EXPLOSION_IMPACTO;
    this->numeroDeAvion = numeroDeAvion;
}

Disparo::~Disparo(){
}

void Disparo::setVelocidad(float velocidad){
	this->velocidad = velocidad;
}

float Disparo::getVelocidad(){
	return this->velocidad;
}

int Disparo::mover(float timeStep){
    pthread_mutex_lock(&this->mutexMover);
    int retorno = 0;
    if(!this->colisiono){
        this->posY -= this->velocidad * timeStep;
        if( this->posY < - ALTO_DISPARO_COMUN){
            retorno = 0;
        } else {
            retorno = 1;
        }
        this->colisionable->mover(this->posX, this->posY, 0, TIPO_DISPARO_AVION);
    }
    else {
        if(this->alturaDeMuerte != -1 && this->posY <= this->alturaDeMuerte ){
            if (this->contadorExplosionImpacto > 0){
                this->estado = 1;
                this->contadorExplosionImpacto -= timeStep;
                retorno = 1;
            } else {
                retorno = 0;
            }
        } else {
            return 1;
        }
    }
    pthread_mutex_unlock(&this->mutexMover);
    return retorno;
}

void Disparo::setPosY(float posY){
    this->posY = posY;
}

float Disparo::getPosY(){
    return this->posY;
}

void Disparo::setPosX(float posX){
    this->posX = posX;
}

float Disparo::getPosX(){
    return this->posX;
}

int Disparo::getAlto(){
    return ALTO_DISPARO_COMUN;
}

int Disparo::getEstado() {
    return this->estado;
}

int Disparo::getAncho(){
    return ANCHO_DISPARO_COMUN;
}

void Disparo::setAvion(int nroAvion){
    nroAvionDisparador = nroAvion;
}

int Disparo::getNroAvion(){
    return nroAvionDisparador;
}

Colisionable* Disparo::getColisionable(){
    return this->colisionable;
}

void Disparo::colisionar(){
    this->colisiono = true;
    this->alturaDeMuerte = this->colisionable->getExtremoSuperior();
}

int Disparo::getNumeroDeAvion() {
    return this->numeroDeAvion;
}