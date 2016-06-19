#include "avionDeEscuadron.hpp"

AvionDeEscuadron::AvionDeEscuadron(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria, int numeroEscuadron){
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
    this->idSprite = SPRITE_AVION_ENEMIGO_PEQUENIO;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->colisionable = new Colisionable(this->posX, this->posY, angulo, TIPO_AVION_ESCUADRON);
    this->tipoAvion = TIPO_AVION_ESCUADRON;
    this->valorImpacto = 100;
    this->valorDerribo = 100;
    this->numeroEscuadron = numeroEscuadron;
}

AvionDeEscuadron::~AvionDeEscuadron(){

}

bool AvionDeEscuadron::correspondeDisparar(float timestep) { return true; }

vector<DisparoEnemigo*> AvionDeEscuadron::disparar(){ vector<DisparoEnemigo*> disparos; return disparos; }

int AvionDeEscuadron::getNumeroEscuadron() {
    return this->numeroEscuadron;
}


