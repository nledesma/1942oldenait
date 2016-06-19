#include "avionMediano.hpp"

AvionMediano::AvionMediano(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->angulo = angulo;
    this->anguloInicial = angulo;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = Trigonomaster::getSpriteAngulo(angulo);
    this->estadoAnimacionInicial = Trigonomaster::getSpriteAngulo(angulo);
    this->idSprite = SPRITE_AVION_ENEMIGO_MEDIANO;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->colisionable = new Colisionable(this->posX, this->posY, angulo, TIPO_AVION_MEDIANO);
    this->tipoAvion = TIPO_AVION_MEDIANO;
    this->vidas = 5;
    this->vidasInicial = 5;
    this->valorImpacto = 100;
    this->valorDerribo = 500;
}

AvionMediano::~AvionMediano(){

}

bool AvionMediano::correspondeDisparar(float timestep) { return true; }


vector<DisparoEnemigo*> AvionMediano::disparar(){  vector<DisparoEnemigo*> disparos; return disparos;  }


int AvionMediano::mover(float timeStep) {
    pthread_mutex_lock(&this->mutexMover);
    int sigueEnPantalla = 1;
    if(this->estadoAnimacion < AVION_ENEMIGO_EXPLOSION_ETAPA_1){
        this->trayectoria->mover(this->posX, this->posY, this->velocidad, this->angulo, this->estadoAnimacion, timeStep);
        // TODO: chequear los bordes usando los atributos del escenario
        if (this->posX > ANCHO_ESCENARIO || this->posX < - this->getAncho()
            || this->posY > ALTO_ESCENARIO || this->posY < - this->getAlto()){
            sigueEnPantalla = 0;
        }
        this->colisionable->mover(this->posX, this->posY, this->angulo, TIPO_AVION_MEDIANO);
    } else {
        if(this->contador > 0 ) {
            this->contador --;
        } else {
            if(this->estadoAnimacion == AVION_ENEMIGO_EXPLOSION_ETAPA_5){
                sigueEnPantalla = 0;
            } else {
                this->estadoAnimacion ++;
            }
            this->contador = CONTADOR_INICIAL;
        }
    }
    pthread_mutex_unlock(&this->mutexMover);
    return sigueEnPantalla;
}

int AvionMediano::estallar(){
    this->colisionar();
    if(this->estadoAnimacion < AVION_ENEMIGO_EXPLOSION_ETAPA_1){
        return this->valorImpacto;
    } else {
        return this->valorDerribo;
    }
}

void AvionMediano::colisionar() {
    this->vidas -= 1;
    if (this->vidas == 0) {
        if (this->estadoAnimacion < AVION_ENEMIGO_EXPLOSION_ETAPA_1) {
            this->estadoAnimacion = AVION_ENEMIGO_EXPLOSION_ETAPA_1;
        }
    }
}

