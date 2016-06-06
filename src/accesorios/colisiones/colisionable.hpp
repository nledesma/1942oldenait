#ifndef INC_1942OLDENAIT_COLISIONABLE_HPP
#define INC_1942OLDENAIT_COLISIONABLE_HPP

#include <iostream>
#include <list>
#include "superficie.hpp"
#include "../codigo.hpp"

using namespace std;

class Colisionable{
private:
    float posX;
    float posY;
    float ancho;
    float alto;
    Superficie* superficiePrincipal;
    list<Superficie*> superficiesSecundarias;
    void crearAvionPequenio(float posX, float posY, float angulo);
    void crearAvionEscuadron(float posX, float posY, float angulo);
    void crearAvionMediano(float posX, float posY, float angulo);
    void crearAvionGrande(float posX, float posY, float angulo);
    void crearAvion(float posX, float posY, float angulo);
    void crearDisparo(float posX, float posY, float angulo);
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
    void mover(float posX, float posY, float angulo);
    Superficie * getSuperficiePrincipal();
    list<Superficie*> getSuperficiesSecundarias();
    float getExtremoIzquierdo();
    float getExtremoDerecho();
    float getExtremoSuperior();
    float getExtremoInferior();
};




#endif
