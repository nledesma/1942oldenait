#ifndef INC_1942OLDENAIT_POWERUPDESTRUIRENEMIGOS_HPP
#define INC_1942OLDENAIT_POWERUPDESTRUIRENEMIGOS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/default.hpp"
#include "powerUp.hpp"

using namespace std;

class PowerUpDestruirEnemigos: public PowerUp {
protected:

public:
		PowerUpDestruirEnemigos(float posicionX, float posicionY, int valor);
    ~PowerUpDestruirEnemigos();
    //virtual void aplicarPowerUp() = 0;
    //int getAncho();
    //int getAlto();
    //float getPosicionX();
    //float getPosicionY();
    //int getEstadoAnimacion();
    //int getTipo();
    //string getIdSprite();
};

#endif //INC_1942OLDENAIT_POWERUPDESTRUIRENEMIGOS_HPP
