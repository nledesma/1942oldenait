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
  int cantidad;
  int valor;
public:
    PowerUpParseado();
    ~PowerUpParseado();
    void setTipo(string tipo);
    void setCantidad(int cantidad);
    void setValor(int valor);
    int getTipo(); //devuelve un int porque directamente se fija en los codigos y devuelve el codigo
    int getCantidad();
    int getValor();
};

#endif //INC_1942OLDENAIT_POWERUP_PARSEADO_HPP
