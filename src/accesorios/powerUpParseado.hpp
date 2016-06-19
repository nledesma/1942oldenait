#ifndef INC_1942OLDENAIT_POWERUP_PARSEADO_HPP
#define INC_1942OLDENAIT_POWERUP_PARSEADO_HPP

#include "codigo.hpp"
#include "default.hpp"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class PowerUpParseado {
private:
  string tipo;
  float posX;
  float posY;
  int valor;
public:
    PowerUpParseado();
    ~PowerUpParseado();
    void setTipo(string tipo);
    void setPosX(float valor);
    void setPosY(float valor);
    void setValor(int valor);
    int getTipo(); //devuelve un int porque directamente se fija en los codigos y devuelve el codigo
    float getPosX();
    float getPosY();
    int getValor();
};

#endif //INC_1942OLDENAIT_POWERUP_PARSEADO_HPP
