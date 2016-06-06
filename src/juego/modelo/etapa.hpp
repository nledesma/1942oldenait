#ifndef ETAPA_H
#define ETAPA_H

#include "elemento.hpp"
#include "avionEnemigo.hpp"
#include "powerUp.hpp"

#include <list>
#include <queue>
using namespace std;

class Etapa {
private:
    int longitud;
    list<Elemento *> elementos;
    list<PowerUp*> powerUps;
    list<pair<float, AvionEnemigo *> > enemigos;
public:
    Etapa(int longitud);
    void agregarElemento(Elemento * e);
    void agregarElemento(float posX, float posY, string idSprite);
    void setEnemigos(list<pair<float, AvionEnemigo *> > enemigos);
    void setPowerUps(list<PowerUp*> powerUps);
    virtual ~Etapa ();
    /* getters & setters */
    int getLongitud();
    list<Elemento *> getElementos();
    list<PowerUp*> getPowerUps();
    AvionEnemigo * getSiguienteEnemigo(float pos);

};

#endif
