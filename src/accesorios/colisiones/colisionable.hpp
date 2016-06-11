#ifndef INC_1942OLDENAIT_COLISIONABLE_HPP
#define INC_1942OLDENAIT_COLISIONABLE_HPP

#include <iostream>
#include <list>
#include "superficie.hpp"
#include "../codigo.hpp"
#include "dimensionSuperficies.hpp"
#include <vector>


using namespace std;

class Colisionable{
private:
    float posX;
    float posY;
    float ancho;
    float alto;
    Superficie* superficiePrincipal;
    vector<Superficie*> superficiesSecundarias;
    int* posCelda;
    void crearAvionPequenio(float posX, float posY, float angulo);
    void crearAvionEscuadron(float posX, float posY, float angulo);
    void crearAvionMediano(float posX, float posY, float angulo);
    void crearAvionGrande(float posX, float posY, float angulo);
    void crearAvion(float posX, float posY, float angulo);
    void crearDisparo(float posX, float posY, float angulo);
    void crearDisparoEnemigo(float posX, float posY, float angulo);



public:
    Colisionable(float posX, float posY, float angulo, int tipoDeElemento);
    ~Colisionable();
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
    void proyectarColisionable(float timeStep);
    Superficie * getSuperficiePrincipal();
    vector<Superficie*> getSuperficiesSecundarias();
    float getExtremoIzquierdo();
    float getExtremoDerecho();
    float getExtremoSuperior();
    float getExtremoInferior();
    void setPosCeldas(int * posCelda);
    int * getPosCeldas();
};




#endif
