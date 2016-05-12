#include "avion.hpp"

using namespace std;

Avion::Avion(float posX, float posY, float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos){
    this->posX = posX;
    this->posY = posY;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->velocidadX = 0;
    this->velocidadY = 0;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->contador = CONTADOR_INICIAL;
    this->estadoAnimacion = ESTADO_NORMAL;
    this->idSprite = idSprite;
    this->idSpriteDisparos = idSpriteDisparos;
}

Avion::~Avion(){

}

void Avion::manejarEvento(int evento){
    /* Se realizan acciones de avión si el mismo no esta loopeando */
    if((this->estadoAnimacion < LOOP_ETAPA_1)) {
        switch (evento) {
            case ARRIBA_PRESIONA:
                this->velocidadY -= this->velocidad;
                break;
            case ABAJO_PRESIONA:
                this->velocidadY += this->velocidad;
                break;
            case IZQUIERDA_PRESIONA:
                this->velocidadX -= this->velocidad;
                this->estadoAnimacion = GIRANDO_IZQUIERDA;
                break;
            case DERECHA_PRESIONA:
                this->estadoAnimacion = GIRANDO_DERECHA;
                this->velocidadX += this->velocidad;
                break;
            case PRESIONA_ESPACIO:
                //this->disparar();
                break;
            case PRESIONA_ENTER:
                this->estadoAnimacion = LOOP_ETAPA_1;
                break;
            case ARRIBA_SUELTA:
                if (this->velocidadY != 0)
                    this->velocidadY += this->velocidad;
                break;
            case ABAJO_SUELTA:
                if (this->velocidadY != 0)
                    this->velocidadY -= this->velocidad;
                break;
            case IZQUIERDA_SUELTA:
                if (this->velocidadX != 0 || this->estadoAnimacion == GIRANDO_DERECHA)
                    this->velocidadX += this->velocidad;
                if (this->estadoAnimacion != GIRANDO_DERECHA)
                    this->estadoAnimacion = ESTADO_NORMAL;
                break;
            case DERECHA_SUELTA:
                if (this->velocidadX != 0 || this->estadoAnimacion == GIRANDO_IZQUIERDA)
                    this->velocidadX -= this->velocidad;
                if (this->estadoAnimacion != GIRANDO_IZQUIERDA)
                    this->estadoAnimacion = ESTADO_NORMAL;
                break;
        }
    }
}

void Avion::mover(float timeStep){
    pthread_mutex_lock(&this->mutexMover);
    if(this->estadoAnimacion < 3) {
        this->posX += this->velocidadX * timeStep;
        if( this->posX < 0 ){
            this->posX = 0;
        }else if( this->posX + this->getAncho() > ANCHO_ESCENARIO){
            this->posX = ANCHO_ESCENARIO - this->getAncho();
        }
        this->posY += this->velocidadY * timeStep;
        if( this->posY < 0 ){
            this->posY = 0;
        } else if ( this->posY + this->getAlto() > ALTO_ESCENARIO){
            this->posY = ALTO_ESCENARIO - this->getAlto();
        }
    } else {
        if(this->estadoAnimacion != DESCONECTADO) {
            if(this->contador > 0) {
                this->contador --;
                if (this->estadoAnimacion >= LOOP_ETAPA_1 && this->estadoAnimacion < LOOP_ETAPA_5){
                    this->posY -= (this->velocidad / 2.f) * timeStep;
                } else if (this->estadoAnimacion >= LOOP_ETAPA_7 && this->estadoAnimacion < LOOP_ETAPA_13){
                    this->posY += (this->velocidad / 2.f) * timeStep;
                }
            } else {
                this->contador = CONTADOR_INICIAL;
                if(this->estadoAnimacion == LOOP_ETAPA_17) {
                    this->estadoAnimacion = 0;
                } else {
                    this->estadoAnimacion ++;
                }
            }
            if (this->estadoAnimacion == LOOP_ETAPA_17){
                this->velocidadX = 0;
                this->velocidadY = 0;
            }
        }
    }
    pthread_mutex_unlock(&this->mutexMover);
}


float Avion::getVelocidad(){
    return this->velocidad;
}

void Avion::setVelocidad(float velocidad){
    this->velocidad = velocidad;
}

float Avion::getPosicionX(){
    pthread_mutex_lock(&this->mutexMover);
    float posicionX = this->posX;
    pthread_mutex_unlock(&this->mutexMover);
    return posicionX;
}
float Avion::getPosicionY(){
    pthread_mutex_lock(&this->mutexMover);
    float posicionY = this->posY;
    pthread_mutex_unlock(&this->mutexMover);
    return posicionY;}

void Avion::setEstadoAnimacion(int estadoAnimacion){
    pthread_mutex_lock(&this->mutexMover);
    this->estadoAnimacion = estadoAnimacion;
    pthread_mutex_unlock(&this->mutexMover);
}

int Avion::getAncho(){
    return AVION_ANCHO;
}
int Avion::getAlto(){
    return AVION_ALTO;
}

int Avion::getAnchoDisparo(){
    return DISPARO_ANCHO;
}

int Avion::getAltoDisparo(){
    return DISPARO_ALTO;
}

int Avion::getEstadoAnimacion(){
    pthread_mutex_lock(&this->mutexMover);
    int estado = this->estadoAnimacion;;
    pthread_mutex_unlock(&this->mutexMover);
    return estado;
}

Disparo* Avion::disparar(){
    // Por ahora sale con la misma velocidad y posición que el avión.
    return new Disparo(this->posX + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f, posY, velocidadDisparos);
}

void Avion::volverEstadoInicial(){
    this->posX = this->posXInicial;
    this->posY = this->posYInicial;
    this->estadoAnimacion = ESTADO_NORMAL;
}

string Avion::getIdSprite(){
    return this->idSprite;
}

string Avion::getIdSpriteDisparos() {
    return this->idSpriteDisparos;
}
