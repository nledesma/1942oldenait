#include "avionPequenio.hpp"

AvionPequenio::AvionPequenio(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->velocidad = velocidad;
    this->angulo = angulo;
    this->anguloInicial = angulo;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = Trigonomaster::getSpriteAngulo(angulo);
    this->estadoAnimacionInicial = Trigonomaster::getSpriteAngulo(angulo);
    this->idSprite = SPRITE_AVION_ENEMIGO_PEQUENIO;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->tipoAvion = TIPO_AVION_PEQUENIO;
    this->colisionable = new Colisionable(this->posX, this->posY, angulo, TIPO_AVION_PEQUENIO);
    this->contador = CONTADOR_INICIAL;
    this->valorImpacto = 50;
    this->valorDerribo = 50;
}

AvionPequenio::~AvionPequenio(){
    delete this->colisionable;
}

bool AvionPequenio::correspondeDisparar(float timestep) { return true; }

vector<DisparoEnemigo*> AvionPequenio::disparar(){  vector<DisparoEnemigo*> disparos; return disparos;  }
