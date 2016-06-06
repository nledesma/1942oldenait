#ifndef INC_1942OLDENAIT_POWERUP_HPP
#define INC_1942OLDENAIT_POWERUP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include "../../accesorios/codigo.hpp"
#include "disparo.hpp"

using namespace std;

class PowerUp {
protected:
  int tipo;
  int valor;
  float posX;
  float posY;
  float posXInicial;
  float posYInicial;
  int estadoAnimacion;
  string idSprite;
public:
    virtual ~PowerUp();
    //virtual void aplicarPowerUp() = 0;
    //virtual float getPosicionX();
    //virtual float getPosicionY();
    //virtual int getEstadoAnimacion();
    virtual int getTipoPowerUp();
    //virtual int getAncho() = 0;
    //virtual int getAlto() = 0;
    //virtual string getIdSprite();
    virtual void mover(float timeStep, float velocidadY);
    virtual void volverEstadoInicial();
};

#endif //INC_1942OLDENAIT_POWERUP_HPP
