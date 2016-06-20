#include "avionSecundario.hpp"

using namespace std;

AvionSecundario::AvionSecundario(float posX, float posY, float velocidad, float velocidadDisparos, string idSpriteDisparos ,float posXFinal, float posYFinal){
    this->posX = posX;
    this->posY = posY;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->posXFinal = posXFinal;
    this->posYFinal = posYFinal;
    this->velocidadX = 0;
    this->velocidadY = 0;
    this->colisionable = new Colisionable(posX, posY, 0, TIPO_AVION_SECUNDARIO);
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_NORMAL;
    this->idSpriteDisparos = idSpriteDisparos;
    this->puntaje = 0;
    this->cantidadDisparos = 0;
    this->cantidadAciertos = 0;
}

AvionSecundario::~AvionSecundario(){

}

void AvionSecundario::manejarEvento(int evento){

    if(this->estadoAnimacion != ESTADO_AVION_SECUNDARIO_DESTRUIDO ) {
        switch (evento) {
            case ARRIBA_PRESIONA:
                this->velocidadY -= this->velocidad;
                break;
            case ABAJO_PRESIONA:
                this->velocidadY += this->velocidad;
                break;
            case IZQUIERDA_PRESIONA:
                this->velocidadX -= this->velocidad;
                this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_GIRANDO_IZQUIERDA;
                break;
            case DERECHA_PRESIONA:
                this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_GIRANDO_DERECHA;
                this->velocidadX += this->velocidad;
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
                if (this->velocidadX != 0 || this->estadoAnimacion == ESTADO_AVION_SECUNDARIO_GIRANDO_DERECHA)
                    this->velocidadX += this->velocidad;
                if (this->estadoAnimacion != ESTADO_AVION_SECUNDARIO_GIRANDO_DERECHA)
                    this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_NORMAL;
                break;
            case DERECHA_SUELTA:
                if (this->velocidadX != 0 || this->estadoAnimacion == ESTADO_AVION_SECUNDARIO_GIRANDO_IZQUIERDA)
                    this->velocidadX -= this->velocidad;
                if (this->estadoAnimacion != ESTADO_AVION_SECUNDARIO_GIRANDO_IZQUIERDA)
                    this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_NORMAL;
                break;
        }
    }
}


void AvionSecundario::mover(float timeStep){
    pthread_mutex_lock(&this->mutexMoverAvionSecundario);
    if (this->estadoAnimacion != ESTADO_AVION_SECUNDARIO_DESTRUIDO) {
        if (this->estadoAnimacion < 3){
            this->posX += this->velocidadX * timeStep;
            if (this->posX < 0) {
                this->posX = 0;
            } else if (this->posX + this->getAncho() > ANCHO_ESCENARIO) {
                this->posX = ANCHO_ESCENARIO - this->getAncho();
            }
            this->posY += this->velocidadY * timeStep;
            if (this->posY < 0) {
                this->posY = 0;
            } else if (this->posY + this->getAlto() > ALTO_ESCENARIO) {
                this->posY = ALTO_ESCENARIO - this->getAlto();
            }
            this->colisionable->mover(this->posX, this->posY, 0, TIPO_AVION_SECUNDARIO);
        }
    }
    pthread_mutex_unlock(&this->mutexMoverAvionSecundario);
}


float AvionSecundario::getVelocidad(){
    return this->velocidad;
}

void AvionSecundario::setVelocidad(float velocidad){
    this->velocidad = velocidad;
}

float AvionSecundario::getPosicionX(){
    pthread_mutex_lock(&this->mutexMoverAvionSecundario);
    float posicionX = this->posX;
    pthread_mutex_unlock(&this->mutexMoverAvionSecundario);
    return posicionX;
}

float AvionSecundario::getPosicionY(){
    pthread_mutex_lock(&this->mutexMoverAvionSecundario);
    float posicionY = this->posY;
    pthread_mutex_unlock(&this->mutexMoverAvionSecundario);
    return posicionY;
}

void AvionSecundario::setEstadoAnimacion(int estadoAnimacion){
    pthread_mutex_lock(&this->mutexMoverAvionSecundario);
    this->estadoAnimacion = estadoAnimacion;
    pthread_mutex_unlock(&this->mutexMoverAvionSecundario);
}

int AvionSecundario::getAncho(){
    return AVION_SECUNDARIO_ANCHO;
}
int AvionSecundario::getAlto(){
    return AVION_SECUNDARIO_ALTO;
}

int AvionSecundario::getAnchoDisparo(){
    return DISPARO_ANCHO;
}

int AvionSecundario::getAltoDisparo(){
    return DISPARO_ALTO;
}

int AvionSecundario::getEstadoAnimacion(){
    pthread_mutex_lock(&this->mutexMoverAvionSecundario);
    int estado = this->estadoAnimacion;
    pthread_mutex_unlock(&this->mutexMoverAvionSecundario);
    return estado;
}

vector<Disparo*> AvionSecundario::disparar(){
    // Por ahora sale con la misma velocidad y posición que el avión.
    vector<Disparo*> disparos;
    if (this->estadoAnimacion != ESTADO_AVION_DESTRUIDO) {
        return disparos;
        this->estadoAnimacion = this->estadoAnimacion + OFFSET_ESTADO_DISPARO;
    }
    return disparos;
}

string AvionSecundario::getIdSprite(){
    return this->idSprite;
}

string AvionSecundario::getIdSpriteDisparos() {
    return this->idSpriteDisparos;
}

void AvionSecundario::setPosicion(float x, float y) {
    posX = x;
    posY = y;
}

void AvionSecundario::sumarPuntos(int puntos) {
    pthread_mutex_lock(&this->mutexPuntaje);
    this->puntaje += puntos;
    pthread_mutex_unlock(&this->mutexPuntaje);
}

Colisionable* AvionSecundario::getColisionable(){
    return this->colisionable;
}

void AvionSecundario::colisionar(){
        if (this->estadoAnimacion < ESTADO_AVION_SECUNDARIO_EXPLOSION_1) {
            this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_EXPLOSION_1;
        }
}

void AvionSecundario::resetPuntos() {
    pthread_mutex_lock(&this->mutexPuntaje);
    this->puntaje = 0;
    pthread_mutex_unlock(&this->mutexPuntaje);
}

int AvionSecundario::getPuntaje() {
    pthread_mutex_lock(&this->mutexPuntaje);
    int puntaje = this->puntaje;
    pthread_mutex_unlock(&this->mutexPuntaje);
    return puntaje;
}

void AvionSecundario::setSpawn(int x, int y) {
    posXInicial = x;
    posYInicial = y;
}

bool AvionSecundario::moverAPosicionFinal(float timeStep) {
    bool resultado = false;
    pthread_mutex_lock(&this->mutexMoverAvionSecundario);
    if (this->estadoAnimacion != ESTADO_AVION_SECUNDARIO_DESTRUIDO) {
        this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_NORMAL;
        if (this->posX != this->posXFinal || this->posY != this->posYFinal) {
            if (this->posX != this->posXFinal) {
                if (this->posX < this->posXFinal) {
                    if ((this->posX + this->velocidad / 2 * timeStep) < this->posXFinal)
                        this->posX += this->velocidad / 2 * timeStep;
                    else
                        this->posX = this->posXFinal;
                } else {
                    if ((this->posX - this->velocidad / 2 * timeStep) > this->posXFinal)
                        this->posX -= this->velocidad * timeStep;
                    else
                        this->posX = this->posXFinal;
                }
            } else {
                if (this->posY < this->posYFinal) {
                    if ((this->posY + this->velocidad / 2 * timeStep) < this->posYFinal)
                        this->posY += this->velocidad / 2 * timeStep;
                    else
                        this->posY = this->posYFinal;
                } else {
                    if ((this->posY - this->velocidad / 2 * timeStep) > this->posYFinal)
                        this->posY -= this->velocidad / 2 * timeStep;
                    else
                        this->posY = this->posYFinal;
                }
            }
        } else {
            this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_NORMAL;
            resultado = true;
        }
    } else {
        resultado = true;
    }
    pthread_mutex_unlock(&this->mutexMoverAvionSecundario);
    return resultado;
}

bool AvionSecundario::estaColisionando(){
    return (this->estadoAnimacion >= ESTADO_AVION_SECUNDARIO_EXPLOSION_1);
}

void AvionSecundario::aumentarAciertos() {
    this->cantidadAciertos ++;
}

int AvionSecundario::getCantidadAciertos() {
    return this->cantidadAciertos;
}

int AvionSecundario::getCantidadDisparos() {
    return this->cantidadDisparos;
}

int AvionSecundario::getPorcentajeAciertos() {
    if (this->cantidadDisparos != 0){
        return (int) floor(100 * (this->cantidadAciertos / (float) this->cantidadDisparos));
    } else {
        return 0;
    }
}
