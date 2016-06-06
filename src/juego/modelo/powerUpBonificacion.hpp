#ifndef INC_1942OLDENAIT_POWERUPBONIFICACION_HPP
#define INC_1942OLDENAIT_POWERUPBONIFICACION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/default.hpp"
#include "disparo.hpp"
#include "powerUp.hpp"

using namespace std;

class PowerUpBonificacion: public PowerUp {
public:
		PowerUpBonificacion(float posX, float posY, int valor);
        ~PowerUpBonificacion();
    //virtual void aplicarPowerUp() = 0;
    //int getAncho();
    //int getAlto();
    //float getPosicionX();
    //float getPosicionY();
    //int getEstadoAnimacion();
    //int getTipo();
    //string getIdSprite();
};

#endif //INC_1942OLDENAIT_POWERUPBONIFICACION_HPP
