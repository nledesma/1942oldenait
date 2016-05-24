#ifndef ETAPAVISTA_H
#define ETAPAVISTA_H

#include "elementoVista.hpp"

class EtapaVista {
private:
    list<ElementoVista *> elementos;
public:
    EtapaVista ();
    virtual ~EtapaVista ();
    void agregarElementoVista(string codigo);
    list<ElementoVista *> getElementos();
};

#endif
