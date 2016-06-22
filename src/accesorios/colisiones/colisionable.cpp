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
             this->crearPowerUp(x,y,0);
             break;
         case TIPO_POWERUP_DESTRUIR_ENEMIGOS:
             this->crearPowerUp(x,y,0);
             break;
         case TIPO_POWERUP_DOS_AMETRALLADORAS:
             this->crearPowerUp(x,y,0);
             break;
         case TIPO_POWERUP_AVIONES_SECUNDARIOS:
             this->crearPowerUp(x,y,0);
             break;
         case TIPO_POWERUP_BONIFICACION_1500:
             this->crearPowerUp(x,y,0);
             break;
    }
}

Colisionable::~Colisionable(){
    delete this->superficiePrincipal;
    for(unsigned int i = 0; i < this->superficiesSecundarias.size(); i++){
        delete this->superficiesSecundarias[i];
    }
}


void Colisionable::crearAvionPequenio(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_PEQUENIO, ALTO_ENEMIGO_PEQUENIO, 0, 0);
    float xCentro = posX + ANCHO_AVION_COMUN / 2;
    float yCentro = posY + ALTO_AVION_COMUN / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro, TIPO_AVION_PEQUENIO);
    Superficie *superficie1 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_2, ALTO_AVION_PEQUENIO_2, AVION_PEQUENIO_OFFSET_ANCHO_DEFAULT, AVION_PEQUENIO_OFFSET_ALTO_DEFAULT);
    Superficie *superficie2 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_1, ALTO_AVION_PEQUENIO_1, AVION_PEQUENIO_OFFSET_ANCHO_DEFAULT, AVION_PEQUENIO_OFFSET_ALTO_DEFAULT);
    Superficie *superficie3 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_1, ALTO_AVION_PEQUENIO_1, AVION_PEQUENIO_OFFSET_ANCHO_DEFAULT, AVION_PEQUENIO_OFFSET_ALTO_DEFAULT + OFFSET_AVION_PEQUENIO_ALTO);
    superficie1->rotar(angulo, xCentro, yCentro, TIPO_AVION_PEQUENIO);
    superficie2->rotar(angulo, xCentro, yCentro, TIPO_AVION_PEQUENIO);
    superficie3->rotar(angulo, xCentro, yCentro, TIPO_AVION_PEQUENIO);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
    this->superficiesSecundarias.push_back(superficie3);
}

void Colisionable::crearAvionEscuadron(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_ESCUADRON, ALTO_ENEMIGO_ESCUADRON, 0, 0);
    float xCentro = posX + ANCHO_ENEMIGO_ESCUADRON / 2;
    float yCentro = posY + ALTO_ENEMIGO_ESCUADRON / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro, TIPO_AVION_ESCUADRON);
    Superficie *superficie1 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_2, ALTO_AVION_PEQUENIO_2, AVION_PEQUENIO_OFFSET_ANCHO_DEFAULT, AVION_PEQUENIO_OFFSET_ALTO_DEFAULT);
    Superficie *superficie2 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_1, ALTO_AVION_PEQUENIO_1, AVION_PEQUENIO_OFFSET_ANCHO_DEFAULT, AVION_PEQUENIO_OFFSET_ALTO_DEFAULT);
    Superficie *superficie3 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_1, ALTO_AVION_PEQUENIO_1, AVION_PEQUENIO_OFFSET_ANCHO_DEFAULT, AVION_PEQUENIO_OFFSET_ALTO_DEFAULT + OFFSET_AVION_PEQUENIO_ALTO);
    superficie1->rotar(angulo, xCentro, yCentro, TIPO_AVION_ESCUADRON);
    superficie2->rotar(angulo, xCentro, yCentro, TIPO_AVION_ESCUADRON);
    superficie3->rotar(angulo, xCentro, yCentro, TIPO_AVION_ESCUADRON);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
    this->superficiesSecundarias.push_back(superficie3);
}

void Colisionable::crearAvionMediano(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_MEDIANO, ALTO_ENEMIGO_MEDIANO, 0, 0);
    float xCentro = posX + ANCHO_ENEMIGO_MEDIANO / 2;
    float yCentro = posY + ALTO_ENEMIGO_MEDIANO / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro, TIPO_AVION_MEDIANO);
    Superficie * superficie1 = new Superficie(posX, posY, AVION_ENEMIGO_MEDIANO_ANCHO_1, AVION_ENEMIGO_MEDIANO_ALTO_1, OFFSET_AVION_ENEMIGO_MEDIANO_ANCHO_1 + OFFSET_ANCHO_AVION_MEDIANO_DEFAULT, OFFSET_AVION_ENEMIGO_MEDIANO_ALTO_1 + OFFSET_ALTO_AVION_MEDIANO_DEFAULT);
    Superficie * superficie2 = new Superficie(posX, posY, AVION_ENEMIGO_MEDIANO_ANCHO_2, AVION_ENEMIGO_MEDIANO_ALTO_2, OFFSET_ANCHO_AVION_MEDIANO_DEFAULT, OFFSET_ALTO_AVION_MEDIANO_DEFAULT);
    Superficie * superficie3 = new Superficie(posX, posY, AVION_ENEMIGO_MEDIANO_ANCHO_2, AVION_ENEMIGO_MEDIANO_ALTO_2, OFFSET_ANCHO_AVION_MEDIANO_DEFAULT, OFFSET_AVION_ENEMIGO_ALTO_2 + OFFSET_ALTO_AVION_MEDIANO_DEFAULT);
    superficie1->rotar(angulo, xCentro, yCentro, TIPO_AVION_MEDIANO);
    superficie2->rotar(angulo, xCentro, yCentro, TIPO_AVION_MEDIANO);
    superficie3->rotar(angulo, xCentro, yCentro, TIPO_AVION_MEDIANO);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
    this->superficiesSecundarias.push_back(superficie3);
}

void Colisionable::crearAvionGrande(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_GRANDE, ALTO_ENEMIGO_GRANDE, 0, 0);
    float xCentro = posX + ANCHO_ENEMIGO_GRANDE / 2;
    float yCentro = posY + ALTO_ENEMIGO_GRANDE / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro, TIPO_AVION_GRANDE);
    Superficie * superficie1 = new Superficie(posX, posY, AVION_ENEMIGO_GRANDE_ANCHO_1, AVION_ENEMIGO_GRANDE_ALTO_1, OFFSET_AVION_ENEMIGO_GRANDE_ANCHO_1 + OFFSET_AVION_ENEMIGO_GRANDE_ANCHO_DEFAULT, OFFSET_AVION_ENEMIGO_GRANDE_ALTO_1 + OFFSET_AVION_ENEMIGO_GRANDE_ALTO_DEFAULT);
    Superficie * superficie2 = new Superficie(posX, posY, AVION_ENEMIGO_GRANDE_ANCHO_2, AVION_ENEMIGO_GRANDE_ALTO_2, OFFSET_AVION_ENEMIGO_GRANDE_ANCHO_DEFAULT, OFFSET_AVION_ENEMIGO_GRANDE_ALTO_2 + OFFSET_AVION_ENEMIGO_GRANDE_ALTO_DEFAULT);
    Superficie * superficie3 = new Superficie(posX, posY, AVION_ENEMIGO_GRANDE_ANCHO_3, AVION_ENEMIGO_GRANDE_ALTO_3, OFFSET_AVION_ENEMIGO_GRANDE_ANCHO_DEFAULT, OFFSET_AVION_ENEMIGO_GRANDE_ALTO_DEFAULT);
    superficie1->rotar(angulo, xCentro, yCentro, TIPO_AVION_GRANDE);
    superficie2->rotar(angulo, xCentro, yCentro, TIPO_AVION_GRANDE);
    superficie3->rotar(angulo, xCentro, yCentro, TIPO_AVION_GRANDE);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
    this->superficiesSecundarias.push_back(superficie3);
}

void Colisionable::crearAvion(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_AVION_COMUN, ALTO_AVION_COMUN, 0, 0);
    float xCentro = posX + ANCHO_AVION_COMUN / 2;
    float yCentro = posY + ALTO_AVION_COMUN / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro, TIPO_AVION);
    Superficie * superficie1 = new Superficie(posX, posY, AVION_ANCHO_1, AVION_ALTO_1, OFFSET_AVION_ANCHO + OFFSET_AVION_ANCHO_DEFAULT, OFFSET_AVION_ALTO_DEFAULT);
    Superficie * superficie2 = new Superficie(posX, posY, AVION_ANCHO_2, AVION_ALTO_2, OFFSET_AVION_ANCHO_DEFAULT, OFFSET_AVION_ALTO + OFFSET_AVION_ALTO_DEFAULT);
    superficie1->rotar(angulo, xCentro, yCentro, TIPO_AVION);
    superficie2->rotar(angulo, xCentro, yCentro, TIPO_AVION);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
}

void Colisionable::crearDisparo(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_SUPERFICIE_DISPARO, ALTO_SUPERFICIE_DISPARO, 0, 0);
    float xCentro = posX + ANCHO_DISPARO_COMUN / 2;
    float yCentro = posY + ALTO_DISPARO_COMUN / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro, TIPO_DISPARO_AVION);
}

void Colisionable::crearDisparoEnemigo(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, DISPARO_ENEMIGO_SUPERFICIE_ANCHO, DISPARO_ENEMIGO_SUPERFICIE_ALTO, 0, 0);
    float xCentro = posX + DISPARO_ENEMIGO_SUPERFICIE_ANCHO / 2;
    float yCentro = posY + DISPARO_ENEMIGO_SUPERFICIE_ALTO / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro, TIPO_DISPARO_ENEMIGO);
}

void Colisionable::crearPowerUp(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX,posY,ANCHO_POWERUP,ALTO_POWERUP,0,0);
    float xCentro = posX + ANCHO_POWERUP / 2;
    float yCentro = posY + ALTO_POWERUP / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro, TIPO_POWERUP);
}


void Colisionable::mover(float posX, float posY, float angulo, int tipoElemento){
    this->superficiePrincipal->mover(posX, posY);
    float xCentral = posX + (this->superficiePrincipal->getAncho() / 2);
    float yCentral = posY + (this->superficiePrincipal->getAlto() / 2);
    for(unsigned int i = 0; i < this->superficiesSecundarias.size(); i++){
        this->superficiesSecundarias[i]->mover(posX, posY);
        this->superficiesSecundarias[i]->rotar(angulo, xCentral, yCentral, tipoElemento);
    }
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


bool Colisionable::colisiona(Colisionable *colisionable) {
    if(!this->superficiePrincipal->colisiona(colisionable->getSuperficiePrincipal())){
        return false;
    }
    if(this->superficiesSecundarias.size() == 0) {
        if(colisionable->getSuperficiesSecundarias().size() == 0){
            return true;
        }
        for(unsigned int i = 0; i < colisionable->getSuperficiesSecundarias().size(); i++){
            if(this->superficiePrincipal->colisiona(colisionable->getSuperficiesSecundarias()[i])){
                return true;
            }
        }
        return false;
    }
    if(colisionable->getSuperficiesSecundarias().size() == 0){
        for(unsigned int i = 0; i < this->superficiesSecundarias.size(); i++){
            if(colisionable->getSuperficiePrincipal()->colisiona(this->superficiesSecundarias[i])){
                return true;
            }
        }
    }
    for(unsigned int i = 0; i < this->superficiesSecundarias.size(); i++){
        for(unsigned int j = 0; j < colisionable->getSuperficiesSecundarias().size(); j++){
            if(this->superficiesSecundarias[i]->colisiona(colisionable->getSuperficiesSecundarias()[j])){
                return true;
            }
        }
    }
    return false;
}

Superficie* Colisionable::getSuperficiePrincipal(){
    return this->superficiePrincipal;
}

vector<Superficie*> Colisionable::getSuperficiesSecundarias(){
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

void Colisionable::setPosCeldas(int *posCelda) {
    this->posCelda = posCelda;
}

int * Colisionable::getPosCeldas(){
    return this->posCelda;
}

void Colisionable::proyectarColisionable(float timeStep) {
    float posY = this->superficiePrincipal->getDerArriba()->getPosY();
    posY += posY * timeStep;
    this->superficiePrincipal->getDerArriba()->setPosY(posY);
    this->superficiePrincipal->getIzqArriba()->setPosY(posY);
}
