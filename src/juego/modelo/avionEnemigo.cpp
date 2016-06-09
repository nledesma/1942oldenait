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

int AvionEnemigo::getAncho() {
    int tipo = this->tipoAvion;
    int ancho;
    if (tipo == TIPO_AVION_PEQUENIO || tipo == TIPO_AVION_ESCUADRON)
        ancho = ANCHO_ENEMIGO_PEQUENIO;
    else if (tipo == TIPO_AVION_MEDIANO)
        ancho = ANCHO_ENEMIGO_MEDIANO;
    else
        ancho = ANCHO_ENEMIGO_GRANDE;
    return ancho;
}


int AvionEnemigo::getAlto() {
    int tipo = this->tipoAvion;
    int alto;
    if (tipo == TIPO_AVION_PEQUENIO || tipo == TIPO_AVION_ESCUADRON)
        alto = ALTO_ENEMIGO_PEQUENIO;
    else if (tipo == TIPO_AVION_MEDIANO)
        alto = ALTO_ENEMIGO_MEDIANO;
    else
        alto = ALTO_ENEMIGO_GRANDE;
    return alto;
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
    if(this->estadoAnimacion < AVION_ENEMIGO_EXPLOSION_ETAPA_1){
        this->trayectoria->mover(this->posX, this->posY, this->velocidad, this->angulo, this->estadoAnimacion, timeStep);
        // TODO: chequear los bordes usando los atributos del escenario
        if (this->posX > ANCHO_ESCENARIO || this->posX < - this->getAncho()
            || this->posY > ALTO_ESCENARIO || this->posY < - this->getAlto()){
            sigueEnPantalla = 0;
        }
        this->colisionable->mover(this->posX, this->posY, this->angulo);
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

Colisionable* AvionEnemigo::getColisionable(){
    return this->colisionable;
}

void AvionEnemigo::colisionar(){
    if(this->estadoAnimacion < AVION_ENEMIGO_EXPLOSION_ETAPA_1){
        this->estadoAnimacion = AVION_ENEMIGO_EXPLOSION_ETAPA_1;
    }
}

DisparoEnemigo* AvionEnemigo::disparar(float xObjetivo, float yObjetivo){
    DisparoEnemigo * disparo;
    if (this->posX != 0) {
        cout << "posX recibida: " << this->posX << " posY recibida: " << this->posY << endl;
        float difX = (float) pow(xObjetivo - this->posX, 2);
        float difY = (float) pow(yObjetivo - this->posY, 2);
        float norma = (float) sqrt(difX + difY);

        float versorX = (xObjetivo - this->posX) / norma;
        float versorY = (yObjetivo - this->posY) / norma;

        float anchoAvion = this->getAncho();
        float altoAvion = this->getAlto();
        float posInicialX = this->posX + anchoAvion / 2.f - ANCHO_DISPARO_ENEMIGO / 2.f;
        float posInicialY = this->posY + altoAvion / 2.f - ALTO_DISPARO_ENEMIGO / 2.f;
        cout << "posX mandada: " << this->posX << " posY mandada: " << this->posY << endl;
        disparo = new DisparoEnemigo(posInicialX, posInicialY, 200, versorX, versorY);
    } else {
        disparo = NULL;
    }

    return disparo;
}