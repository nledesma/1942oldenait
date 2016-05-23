#ifndef ETAPA_H
#define ETAPA_H

#include "elemento.hpp"

#include <list>
using namespace std;

class Etapa {
private:
    int longitud;
    list<Elemento *> elementos;

    // NOTE se agregará lista de enemigos.
public:
    Etapa(int longitud);
    void agregarElemento(Elemento * e);
    void agregarElemento(float posX, float posY, string idSprite);
    virtual ~Etapa ();
    /* getters & setters */
    int getLongitud();
    list<Elemento *> getElementos();
};

#endif
