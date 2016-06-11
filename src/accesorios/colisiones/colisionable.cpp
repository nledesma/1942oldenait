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
    }
}

Colisionable::~Colisionable(){
    delete this->superficiePrincipal;
    for(list<Superficie*>::iterator itSuperficies = this->superficiesSecundarias.begin(); itSuperficies != this->superficiesSecundarias.end(); itSuperficies++){
        delete (*itSuperficies);
    }
}


void Colisionable::crearAvionPequenio(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_PEQUENIO, ALTO_ENEMIGO_PEQUENIO, 0, 0);
    float xCentro = posX + ANCHO_AVION_COMUN / 2;
    float yCentro = posY + ALTO_AVION_COMUN / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
    Superficie *superficie1 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_1, ANCHO_AVION_PEQUENIO_1, 0, AVION_PEQUENIO_OFFSET_ALTO);
    Superficie *superficie2 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_2, ALTO_AVION_PEQUENIO_2, 0, 0);
    Superficie *superficie3 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_2, ALTO_AVION_PEQUENIO_2, AVION_PEQUENIO_OFFSET_ANCHO, 0);
    superficie1->rotar(angulo, xCentro, yCentro);
    superficie2->rotar(angulo, xCentro, yCentro);
    superficie3->rotar(angulo, xCentro, yCentro);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
    this->superficiesSecundarias.push_back(superficie3);
}

void Colisionable::crearAvionEscuadron(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_ESCUADRON, ALTO_ENEMIGO_ESCUADRON, 0, 0);
    float xCentro = posX + ANCHO_ENEMIGO_ESCUADRON / 2;
    float yCentro = posY + ALTO_ENEMIGO_ESCUADRON / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
    Superficie *superficie1 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_1, ANCHO_AVION_PEQUENIO_1, 0, AVION_PEQUENIO_OFFSET_ALTO);
    Superficie *superficie2 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_2, ALTO_AVION_PEQUENIO_2, 0, 0);
    Superficie *superficie3 = new Superficie(posX, posY, ANCHO_AVION_PEQUENIO_2, ALTO_AVION_PEQUENIO_2, AVION_PEQUENIO_OFFSET_ANCHO, 0);
    superficie1->rotar(angulo, xCentro, yCentro);
    superficie2->rotar(angulo, xCentro, yCentro);
    superficie3->rotar(angulo, xCentro, yCentro);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
    this->superficiesSecundarias.push_back(superficie3);
}

void Colisionable::crearAvionMediano(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_MEDIANO, ALTO_ENEMIGO_MEDIANO, 0, 0);
    float xCentro = posX + ANCHO_ENEMIGO_MEDIANO / 2;
    float yCentro = posY + ALTO_ENEMIGO_MEDIANO / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
    Superficie * superficie1 = new Superficie(posX, posY, AVION_ENEMIGO_MEDIANO_ANCHO_1, AVION_ENEMIGO_MEDIANO_ALTO_1, 0, 0);
    Superficie * superficie2 = new Superficie(posX, posY, AVION_ENEMIGO_MEDIANO_ANCHO_2, AVION_ENEMIGO_MEDIANO_ALTO_2, OFFSET_ANCHO_AVION_MEDIANO, OFFSET_ALTO_AVION_MEDIANO);
    Superficie * superficie3 = new Superficie(posX, posY, AVION_ENEMIGO_MEDIANO_ANCHO_1, AVION_ENEMIGO_MEDIANO_ALTO_1, OFFSET_ANCHO_AVION_MEDIANO_2, 0);
    superficie1->rotar(angulo, xCentro, yCentro);
    superficie2->rotar(angulo, xCentro, yCentro);
    superficie3->rotar(angulo, xCentro, yCentro);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
    this->superficiesSecundarias.push_back(superficie3);
}

void Colisionable::crearAvionGrande(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_ENEMIGO_GRANDE, ALTO_ENEMIGO_GRANDE, 0, 0);
    float xCentro = posX + ANCHO_ENEMIGO_GRANDE / 2;
    float yCentro = posY + ALTO_ENEMIGO_GRANDE / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
    Superficie * superficie1 = new Superficie(posX, posY, AVION_ENEMIGO_GRANDE_ANCHO_1, AVION_ENEMIGO_GRANDE_ALTO_1, OFFSET_ANCHO_AVION_GRANDE, 0);
    Superficie * superficie2 = new Superficie(posX, posY, AVION_ENEMIGO_GRANDE_ANCHO_2, AVION_ENEMIGO_GRANDE_ALTO_2, 0, 0);
    superficie1->rotar(angulo, xCentro, yCentro);
    superficie2->rotar(angulo, xCentro, yCentro);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
}

void Colisionable::crearAvion(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_AVION_COMUN, ALTO_AVION_COMUN, 0, 0);
    float xCentro = posX + ANCHO_AVION_COMUN / 2;
    float yCentro = posY + ALTO_AVION_COMUN / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
    Superficie * superficie1 = new Superficie(posX, posY, AVION_ANCHO_1, AVION_ALTO_1, OFFSET_AVION_ANCHO, 0);
    Superficie * superficie2 = new Superficie(posX, posY, AVION_ANCHO_2, AVION_ALTO_2, 0, OFFSET_AVION_ALTO);
    superficie1->rotar(angulo, xCentro, yCentro);
    superficie2->rotar(angulo, xCentro, yCentro);
    this->superficiesSecundarias.push_back(superficie1);
    this->superficiesSecundarias.push_back(superficie2);
}

void Colisionable::crearDisparo(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, ANCHO_SUPERFICIE_DISPARO, ALTO_SUPERFICIE_DISPARO, 0, 0);
    float xCentro = posX + ANCHO_DISPARO_COMUN / 2;
    float yCentro = posY + ALTO_DISPARO_COMUN / 2;
    this->superficiePrincipal->rotar(angulo, xCentro, yCentro);
}

void Colisionable::crearDisparoEnemigo(float posX, float posY, float angulo){
    this->superficiePrincipal = new Superficie(posX, posY, DISPARO_ENEMIGO_SUPERFICIE_ANCHO, DISPARO_ENEMIGO_SUPERFICIE_ALTO, 0, 0);
    float xCentro = posX + DISPARO_ENEMIGO_SUPERFICIE_ANCHO / 2;
    float yCentro = posY + DISPARO_ENEMIGO_SUPERFICIE_ALTO / 2;
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

/*bool Colisionable::colisiona(Colisionable *colisionable){
    bool colisiona = this->superficiePrincipal->colisiona(colisionable->getSuperficiePrincipal());
    if(colisiona && this->superficiesSecundarias.size() > 0){
        colisiona = false;
        list<Superficie*>::iterator itSuperficies = this->superficiesSecundarias.begin();
        int i = 0;
        cout << this->superficiesSecundarias.size() << endl;
        while(!colisiona || (itSuperficies != this->superficiesSecundarias.end())) {

            if(colisionable->getSuperficiePrincipal()->colisiona((*itSuperficies))){
                if(colisionable->getSuperficiesSecundarias().size() == 0) {
                    colisiona = true;
                } else {
                    list<Superficie *>::iterator itSuperficiesColisionable = colisionable->getSuperficiesSecundarias().begin();
                     while (!colisiona || (itSuperficiesColisionable != colisionable->getSuperficiesSecundarias().end())) {
                         colisiona = (*itSuperficies)->colisiona((*itSuperficiesColisionable));
                         itSuperficiesColisionable++;
                     }
                }
             }
             itSuperficies++;
            cout<< i << endl << endl;
            i++;
         }
     }
    return colisiona;
}*/

bool Colisionable::colisiona(Colisionable *colisionable) {

    if(!this->superficiePrincipal->colisiona(colisionable->getSuperficiePrincipal())){
        return false;
    }

    if(this->superficiesSecundarias.size() == 0) {
        if(colisionable->getSuperficiePrincipal() == 0){
            return true;
        }
        for(list<Superficie*>::iterator itSuperficie = colisionable->getSuperficiesSecundarias().begin(); itSuperficie != colisionable->getSuperficiesSecundarias().end(); itSuperficie++){
            if(this->superficiePrincipal->colisiona((*itSuperficie))){
                return true;
            }
        }
        return false;
    }
    for(list<Superficie*>::iterator itSuperficie = this->superficiesSecundarias.begin(); itSuperficie != this->superficiesSecundarias.end(); itSuperficie++){
        for(list<Superficie*>::iterator itSuperficie2 = colisionable->getSuperficiesSecundarias().begin(); itSuperficie2 != colisionable->getSuperficiesSecundarias().end(); itSuperficie2++){
            if((*itSuperficie)->colisiona((*itSuperficie2))){
                return true;
            }
            cout<<"aca llega" << endl;
        }
    }
    return false;
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