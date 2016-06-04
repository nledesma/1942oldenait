#ifndef INC_1942OLDENAIT_PUNTO_HPP
#define INC_1942OLDENAIT_PUNTO_HPP

#include "../trigonomaster.hpp"
#include <iostream>

using namespace std;

class Punto{

private:
    float posX;
    float posY;

public:
    Punto(float posX, float posY);
    void setPosX(float posX);
    float getPosX();
    void setPosY(float posY);
    float getPosY();
    float productoPunto(Punto * punto);
    void mover(float x, float y);
    void rotar(float angulo, float x, float y);
};

#endif
