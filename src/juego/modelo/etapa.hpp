#ifndef ETAPA_H
#define ETAPA_H

#include "elemento.hpp"
#include "avionEnemigo.hpp"

#include <list>
#include <queue>
using namespace std;

class Etapa {
private:
    int longitud;
    list<Elemento *> elementos;
    list<pair<float, AvionEnemigo *> > enemigos;
public:
    Etapa(int longitud);
    void agregarElemento(Elemento * e);
    void agregarElemento(float posX, float posY, string idSprite);
    void setEnemigos(list<pair<float, AvionEnemigo *> > enemigos);
    virtual ~Etapa ();
    /* getters & setters */
    int getLongitud();
    list<Elemento *> getElementos();
    AvionEnemigo * getSiguienteEnemigo(float pos);

};

#endif
