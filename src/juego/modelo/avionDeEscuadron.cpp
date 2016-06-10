#include "avionDeEscuadron.hpp"

AvionDeEscuadron::AvionDeEscuadron(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->angulo = angulo;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = Trigonomaster::getSpriteAngulo(angulo);
    this->idSprite = SPRITE_AVION_ENEMIGO_PEQUENIO;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->colisionable = new Colisionable(this->posX, this->posY, angulo, TIPO_AVION_ESCUADRON);
    this->tipoAvion = TIPO_AVION_ESCUADRON;
}

AvionDeEscuadron::~AvionDeEscuadron(){

}

bool AvionDeEscuadron::correspondeDisparar(float timestep) { return true; }

vector<DisparoEnemigo*> AvionDeEscuadron::disparar(){ vector<DisparoEnemigo*> disparos; return disparos; }