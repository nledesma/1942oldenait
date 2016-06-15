#include "etapa.hpp"

Etapa::Etapa(int longitud) {
    this->longitud = longitud;
    this->etapaActiva = true;
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
    float hola = (*itEnemigos).first;
    hola ++;
    if (!this->enemigos.empty() && this->itEnemigos != this->enemigos.end()){
        if (pos >= (*itEnemigos).first){
            pair <float, AvionEnemigo*> proximoPar;
            proximoPar = *itEnemigos;
            //this->enemigos.pop_front();
            itEnemigos++;
            return proximoPar.second;
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
    this->itEnemigos = this->enemigos.begin();
}

void Etapa::setPowerUps(list<PowerUp*> powerUps){
  this->powerUps = powerUps;
}

void Etapa::reiniciarEtapa() {
    this->itEnemigos = this->enemigos.begin();
}

bool Etapa::etapaEstaActiva() {
    return this->etapaActiva;
}

void Etapa::desactivarEtapa() {
    this->etapaActiva = false;
}
