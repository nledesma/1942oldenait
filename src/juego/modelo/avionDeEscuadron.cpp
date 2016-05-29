#include "avionDeEscuadron.hpp"

AvionDeEscuadron::AvionDeEscuadron(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = Trigonomaster::getSpriteAngulo(angulo);
    this->idSprite = SPRITE_AVION_ENEMIGO_PEQUENIO;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->tipoAvion = TIPO_AVION_ESCUADRON;
}

AvionDeEscuadron::~AvionDeEscuadron(){

}

Disparo* AvionDeEscuadron::disparar(){
    return NULL;
}

int AvionDeEscuadron::getAncho() {
    return ANCHO_ENEMIGO_PEQUENIO;
}

int AvionDeEscuadron::getAlto() {
    return ALTO_ENEMIGO_PEQUENIO;
}

int AvionDeEscuadron::mover(float timeStep){
    return AvionEnemigo::mover(timeStep);
}

float AvionDeEscuadron::getVelocidad(){
    return AvionEnemigo::getVelocidad();
}

float AvionDeEscuadron::getPosicionX(){
    return AvionEnemigo::getPosicionX();
}

float AvionDeEscuadron::getPosicionY(){
    return AvionEnemigo::getPosicionY();
}

float AvionDeEscuadron::getAngulo(){
    return AvionEnemigo::getAngulo();
}

int AvionDeEscuadron::getEstadoAnimacion(){
    return AvionEnemigo::getEstadoAnimacion();
}

int AvionDeEscuadron::getTipoAvion(){
    return AvionEnemigo::getTipoAvion();
}

int AvionDeEscuadron::getAnchoDisparo(){
    return AvionEnemigo::getAnchoDisparo();
}

int AvionDeEscuadron::getAltoDisparo(){
    return AvionEnemigo::getAltoDisparo();
}

string AvionDeEscuadron::getIdSprite(){
    return AvionEnemigo::getIdSprite();
}

string AvionDeEscuadron::getIdSpriteDisparos(){
    return AvionEnemigo::getIdSpriteDisparos();
}
