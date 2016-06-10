#include "colisionable.hpp"

Colisionable::Colisionable(float x, float y, float angulo, int tipoDeElemento){
    this->posX = x;
    this->posY = y;
    this->ancho = ancho;
    this->alto = alto;
    switch (tipoDeElemento) {
        case TIPO_AVION_PEQUENIO:
            this->crearAvionPequenio(x, y, angulo);
            break;
        case TIPO_AVION_ESCUADRON:
            this->crearAvionEscuadron(x, y, angulo);
            break;
        case TIPO_AVION_MEDIANO:
            this->crearAvionMediano(x, y, angulo);
            break;
        case TIPO_AVION_GRANDE:
            this->crearAvionGrande(x, y, angulo);
            break;
        case TIPO_AVION:
            this->crearAvion(x, y, angulo);
            break;
        case TIPO_DISPARO_AVION:
            this->crearDisparo(x, y, angulo);
            break;
        case TIPO_DISPARO_ENEMIGO:
            this->crearDisparoEnemigo(x, y, angulo);
            break;
        case TIPO_POWERUP_BONIFICACION:
            this->crearPowerUp(x,y,angulo);
            break;
        case TIPO_POWERUP_DOS_AMETRALLADORAS:
            this->crearPowerUp(x,y,angulo);
            break;
        case TIPO_POWERUP_DESTRUIR_ENEMIGOS:
            this->crearPowerUp(x,y,angulo);
            break;
        case TIPO_POWERUP_AVIONES_SECUNDARIOS:
            this->crearPowerUp(x,y,angulo);
            break;
        case TIPO_POWERUP_BONIFICACION_1500:
            this->crearPowerUp(x,y,angulo);
            break;
    }
}


void Colisionable::crearAvionPequenio(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_PEQUENIO, ALTO_ENEMIGO_PEQUENIO, 0, 0);
    float xCentro = (posX + ANCHO_AVION_COMUN) / 2;
    float yCentro = (posY + ALTO_AVION_COMUN) / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

void Colisionable::crearAvionEscuadron(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_ESCUADRON, ALTO_ENEMIGO_ESCUADRON, 0, 0);
    float xCentro = (posX + ANCHO_ENEMIGO_ESCUADRON) / 2;
    float yCentro = (posY + ALTO_ENEMIGO_ESCUADRON) / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

void Colisionable::crearAvionMediano(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_MEDIANO, ALTO_ENEMIGO_MEDIANO, 0, 0);
    float xCentro = (posX + ANCHO_ENEMIGO_MEDIANO) / 2;
    float yCentro = (posY + ALTO_ENEMIGO_MEDIANO) / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

void Colisionable::crearAvionGrande(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_GRANDE, ALTO_ENEMIGO_GRANDE, 0, 0);
    float xCentro = (posX + ANCHO_ENEMIGO_GRANDE) / 2;
    float yCentro = (posY + ALTO_ENEMIGO_GRANDE) / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

void Colisionable::crearAvion(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_AVION_COMUN, ALTO_AVION_COMUN, 0, 0);
    float xCentro = (posX + ANCHO_AVION_COMUN) / 2;
    float yCentro = (posY + ALTO_AVION_COMUN) / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

void Colisionable::crearDisparo(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_DISPARO_COMUN, ALTO_DISPARO_COMUN, 0, 0);
    float xCentro = (posX + ANCHO_DISPARO_COMUN) / 2;
    float yCentro = (posY + ALTO_DISPARO_COMUN) / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

void Colisionable::crearDisparoEnemigo(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_DISPARO_ENEMIGO, ALTO_DISPARO_ENEMIGO, 0, 0);
    float xCentro = (posX + ANCHO_DISPARO_ENEMIGO) / 2;
    float yCentro = (posY + ALTO_DISPARO_ENEMIGO) / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

void Colisionable::mover(float posX, float posY, float angulo){
    this->superficiePrincipal->mover(posX, posY);
    float xCentral = posX + (this->superficiePrincipal->getAncho() / 2);
    float yCentral = posY + (this->superficiePrincipal->getAncho() / 2);
    this->superficiePrincipal->rotar(angulo, xCentral, yCentral);
    for(list<Superficie*>::iterator itSuperficies = superficiesSecundarias.begin(); itSuperficies != superficiesSecundarias.end(); itSuperficies++){
        (*itSuperficies)->mover(posX, posY);
        (*itSuperficies)->rotar(angulo, xCentral, yCentral);
    }
}
void Colisionable::crearPowerUp(float posX, float posY, float angulo){ //TODO: REVISAR SI ESE ANGULO SIRVE PARA ALGO O ES SARASA
    this->superficiePrincipal = new Superficie(posX,posY,ANCHO_POWERUP,ALTO_POWERUP,0,0);
    float xCentro = (posX + ANCHO_POWERUP) / 2;
    float yCentro = (posY + ALTO_POWERUP) / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

float Colisionable::getPosX(){
    return this->posX;
}

float Colisionable::getPosY(){
    return this->posY;
}

float Colisionable::getAncho(){
    return this->ancho;
}

float Colisionable::getAlto(){
    return this->alto;
}

void Colisionable::setPosX(float posX){
    this->posX = posX;
}

void Colisionable::setPosY(float posY){
    this->posY = posY;
}

// bool Colisionable::colisiona(Colisionable * colisionable){
//     int izquierda, izquierdaColisionable;
//     int derecha, derechaColisionable;
//     int arriba, arribaColisionable;
//     int abajo, abajoColisionable;
//
//     izquierda = this->posX;
//     derecha = this->posX + this->ancho;
//     arriba = this->posY;
//     abajo = this->posY + this->alto;
//
//     izquierdaColisionable = colisionable->getPosX();
//     derechaColisionable = colisionable->getPosX() + colisionable->getAncho();
//     arribaColisionable = colisionable->getPosY();
//     abajoColisionable = colisionable->getPosY() + colisionable->getAlto();
//
//
//     if((arribaColisionable <= 0) || (abajo <= arribaColisionable)){
//             return false;
//     }
//
//     if((abajoColisionable <= 0) || (arriba >= abajoColisionable)){
//             return false;
//     }
//
//     if(derecha <= izquierdaColisionable){
//         return false;
//     }
//
//     if(izquierda >= derechaColisionable){
//         return false;
//     }
//
//     return true;
// }

bool Colisionable::colisiona(Colisionable *colisionable){
    bool resultado = this->superficiePrincipal->colisiona(colisionable->getSuperficiePrincipal());
    // if(this->superficiePrincipal->colisiona(colisionable->getSuperficiePrincipal())){
    //     bool colisiona = false;
    //     list<Superficie*>::iterator itSuperficies = this->superficiesSecundarias.begin();
    //     while(!colisiona && itSuperficies != this->superficiesSecundarias.end()){
    //         list<Superficie*>::iterator itSuperficiesColisionable = colisionable->getSuperficiesSecundarias().begin();
    //         while(!colisiona && itSuperficiesColisionable != colisionable->getSuperficiesSecundarias().end()){
    //             colisiona = (*itSuperficies)->colisiona((*itSuperficiesColisionable));
    //             itSuperficiesColisionable++;
    //         }
    //         itSuperficies++;
    //     }
    //     return colisiona;
    // } else {
    //     return false;
    // }
    return resultado;
}

Superficie* Colisionable::getSuperficiePrincipal(){
    return this->superficiePrincipal;
}

list<Superficie*> Colisionable::getSuperficiesSecundarias(){
    return this->superficiesSecundarias;
}

float Colisionable::getExtremoIzquierdo(){
    float extremoIzquierdo = superficiePrincipal->getDerAbajo()->getPosX();

    if(extremoIzquierdo > superficiePrincipal->getIzqAbajo()->getPosX()){
        extremoIzquierdo = superficiePrincipal->getIzqAbajo()->getPosX();
    }

    if(extremoIzquierdo > superficiePrincipal->getIzqArriba()->getPosX()){
        extremoIzquierdo  = superficiePrincipal->getIzqArriba()->getPosX();
    }

    if(extremoIzquierdo > superficiePrincipal->getDerArriba()->getPosX()){
        extremoIzquierdo = superficiePrincipal->getDerArriba()->getPosX();
    }

    return extremoIzquierdo;
}

float Colisionable::getExtremoDerecho(){

    float extremoDerecho = this->superficiePrincipal->getDerAbajo()->getPosX();

    if(extremoDerecho < this->superficiePrincipal->getIzqAbajo()->getPosX()){
        extremoDerecho = this->superficiePrincipal->getIzqAbajo()->getPosX();
    }

    if(extremoDerecho < this->superficiePrincipal->getIzqArriba()->getPosX()){
        extremoDerecho  = this->superficiePrincipal->getIzqArriba()->getPosX();
    }

    if(extremoDerecho < this->superficiePrincipal->getDerArriba()->getPosX()){
        extremoDerecho = this->superficiePrincipal->getDerArriba()->getPosX();
    }

    return extremoDerecho;
}

float Colisionable::getExtremoSuperior(){

    float extremoSuperior = superficiePrincipal->getDerAbajo()->getPosY();

    if(extremoSuperior < superficiePrincipal->getIzqAbajo()->getPosY()){
        extremoSuperior = superficiePrincipal->getIzqAbajo()->getPosY();
    }

    if(extremoSuperior < superficiePrincipal->getIzqArriba()->getPosY()){
        extremoSuperior  = superficiePrincipal->getIzqArriba()->getPosY();
    }

    if(extremoSuperior < superficiePrincipal->getDerArriba()->getPosY()){
        extremoSuperior = superficiePrincipal->getDerArriba()->getPosY();
    }

    return extremoSuperior;
}

float Colisionable::getExtremoInferior(){

    float extremoInferior = superficiePrincipal->getDerAbajo()->getPosY();

    if(extremoInferior > superficiePrincipal->getIzqAbajo()->getPosY()){
        extremoInferior = superficiePrincipal->getIzqAbajo()->getPosY();
    }

    if(extremoInferior > superficiePrincipal->getIzqArriba()->getPosY()){
        extremoInferior  = superficiePrincipal->getIzqArriba()->getPosY();
    }

    if(extremoInferior > superficiePrincipal->getDerArriba()->getPosY()){
        extremoInferior = superficiePrincipal->getDerArriba()->getPosY();
    }

    return extremoInferior;
}
