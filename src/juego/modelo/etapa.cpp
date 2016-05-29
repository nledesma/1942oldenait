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
    if (!this->enemigos.empty()){
        if (pos >= this->enemigos.front().first){
            pair <float, AvionEnemigo*> proximoPar;
            proximoPar = this->enemigos.front();
            this->enemigos.pop();
            return proximoPar.second;
        }
    }
    return NULL;
}

list<Elemento *> Etapa::getElementos() {
    // devuelve una copia de la lista de elementos.
    return elementos;
}
