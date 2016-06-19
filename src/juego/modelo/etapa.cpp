#include "etapa.hpp"

Etapa::Etapa(int longitud) {
    this->longitud = longitud;
}

Etapa::~Etapa() {
    // Libero memoria.
    list<Elemento *>::iterator it;
    for (it = elementos.begin(); it != elementos.end(); ++it) {
        delete *it;
    }
}

void Etapa::agregarElemento(Elemento * e) {
    elementos.push_back(e);
}

void Etapa::agregarElemento(float posX, float posY, string idSprite) {
    Elemento *elemento = new Elemento(posX, posY, idSprite);
    this->elementos.push_back(elemento);
}

/* getters & setters */

int Etapa::getLongitud() {
    return longitud;
}

AvionEnemigo* Etapa::getSiguienteEnemigo(float pos) {
    if (itEnemigos != enemigos.end()){
        pair <float, AvionEnemigo*> avionEnemigo = (*itEnemigos);
        if (pos >= avionEnemigo.first){
            ++itEnemigos;
            return avionEnemigo.second;
        }
    }
    return NULL;
}

list<Elemento *> Etapa::getElementos() {
    // devuelve una copia de la lista de elementos.
    return elementos;
}

list<PowerUp*> Etapa::getPowerUps(){
  return powerUps;
}

void Etapa::setEnemigos(list<pair<float, AvionEnemigo *> > enemigos) {
    this->enemigos = enemigos;
    this->itEnemigos = begin(this->enemigos);
}

void Etapa::resetEnemigos(){
    this->itEnemigos = begin(this->enemigos);
}

void Etapa::setPowerUps(list<PowerUp*> powerUps){
  this->powerUps = powerUps;
}

void Etapa::setEstadosIniciales() {
    for (list<Elemento *>::iterator itElementos = elementos.begin(); itElementos != elementos.end(); itElementos++) {
        (*itElementos)->volverEstadoInicial();
    }
    for (list<PowerUp *>::iterator itPowerUps = powerUps.begin(); itPowerUps != powerUps.end(); itPowerUps++) {
        (*itPowerUps)->volverEstadoInicial();
    }
    for (list<pair<float, AvionEnemigo *> >::iterator itParesEnemigos = enemigos.begin(); itParesEnemigos != enemigos.end(); itParesEnemigos++) {
        (*itParesEnemigos).second->setEstadoInicial();
    }
}
