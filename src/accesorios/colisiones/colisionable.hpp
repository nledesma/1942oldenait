#ifndef INC_1942OLDENAIT_COLISIONABLE_HPP
#define INC_1942OLDENAIT_COLISIONABLE_HPP

#include <iostream>
#include <list>
#include "superficie.hpp"

using namespace std;

class Colisionable{
private:
    float posX;
    float posY;
    float ancho;
    float alto;
    Superficie* superficiePrincipal;
    list<Superficie*> superficiesSecundarias;
    void crearAvion(float posX, float posY, float angulo);
    void crearDisparo(float posX, float posY, float angulo);
    void crearEnemigo(float posX, float posY, float angulo);
    void crearDisparoEnemigo(float posX, float posY, float angulo);

public:
    Colisionable(float posX, float posY, float angulo, int tipoDeElemento);
    float getPosX();
    float getPosY();
    void setPosX(float posX);
    void setPosY(float posY);
    float getAncho();
    float getAlto();
    float getAngulo();
    void setAngulo(float angulo);
    bool colisiona(Colisionable * colisionable);
    Superficie * getSuperficiePrincipal();
    list<Superficie*> getSuperficiesSecundarias();
};


#endif
