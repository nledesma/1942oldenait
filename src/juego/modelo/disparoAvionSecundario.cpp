#include "disparoAvionSecundario.hpp"

DisparoAvionSecundario::DisparoAvionSecundario(float posX, float posY, float velocidad){
    this->posX = posX;
    this->posY = posY;
    this->velocidad = velocidad;
    this->colisionable = new Colisionable(this->posX, this->posY, 0, TIPO_DISPARO_AVION);
    this->colisiono = false;
    this->alturaDeMuerte = -1;
    this->estado = 0;
    this->contadorExplosionImpacto = TIEMPO_EXPLOSION_IMPACTO;
    // this->numeroDeAvion = numeroDeAvion;
}

DisparoAvionSecundario::~DisparoAvionSecundario(){
}

void DisparoAvionSecundario::setVelocidad(float velocidad){
	this->velocidad = velocidad;
}

float DisparoAvionSecundario::getVelocidad(){
	return this->velocidad;
}

int DisparoAvionSecundario::mover(float timeStep){
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

void DisparoAvionSecundario::setPosY(float posY){
    this->posY = posY;
}

float DisparoAvionSecundario::getPosY(){
    return this->posY;
}

void DisparoAvionSecundario::setPosX(float posX){
    this->posX = posX;
}

float DisparoAvionSecundario::getPosX(){
    return this->posX;
}

int DisparoAvionSecundario::getAlto(){
    return ALTO_DISPARO_COMUN;
}

int DisparoAvionSecundario::getEstado() {
    return this->estado;
}

int DisparoAvionSecundario::getAncho(){
    return ANCHO_DISPARO_COMUN;
}

void DisparoAvionSecundario::setAvion(int nroAvion){
    nroAvionDisparador = nroAvion;
}

int DisparoAvionSecundario::getNroAvion(){
    return nroAvionDisparador;
}

Colisionable* DisparoAvionSecundario::getColisionable(){
    return this->colisionable;
}

void DisparoAvionSecundario::colisionar(){
    this->colisiono = true;
    this->alturaDeMuerte = this->colisionable->getExtremoSuperior();
}

int DisparoAvionSecundario::getNumeroDeAvion() {
    return this->numeroDeAvion;
}
