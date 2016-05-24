#include "etapaVista.hpp"

EtapaVista::EtapaVista () {

}

EtapaVista::~EtapaVista () {

}

void EtapaVista::agregarElementoVista(string codigo){
    //Agrega el elemento a la lista.
    ElementoVista* elementoVista = new ElementoVista(codigo);
    this->elementos.push_back(elementoVista);
}

list<ElementoVista *> EtapaVista::getElementos() {
    return elementos;
}
