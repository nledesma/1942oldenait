#include "avionGrande.hpp"

AvionGrande::AvionGrande(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = Trigonomaster::getSpriteAngulo(angulo);
    this->idSprite = SPRITE_AVION_ENEMIGO_GRANDE;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->tipoAvion = TIPO_AVION_GRANDE;
}

AvionGrande::~AvionGrande(){

}

Disparo* AvionGrande::disparar(){
    return NULL;
}

int AvionGrande::getAncho() {
    return ANCHO_ENEMIGO_GRANDE;
}

int AvionGrande::getAlto() {
    return ALTO_ENEMIGO_GRANDE;
}
