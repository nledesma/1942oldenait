#ifndef INC_1942OLDENAIT_COLISIONABLE_HPP
#define INC_1942OLDENAIT_COLISIONABLE_HPP

#include <iostream>

using namespace std;

class Colisionable{
private:
    float posX;
    float posY;
    float ancho;
    float alto;
    float angulo;

public:
    Colisionable(float x, float y, float ancho, float alto);
    Colisionable(float x, float y, float ancho, float alto, float angulo);
    float getPosX();
    float getPosY();
    void setPosX(float posX);
    void setPosY(float posY);
    float getAncho();
    float getAlto();
    float getAngulo();
    void setAngulo(float angulo);
    bool colisiona(Colisionable * colisionable);
};


#endif
