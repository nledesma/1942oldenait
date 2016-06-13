#ifndef INC_1942OLDENAIT_POWERUPBONIFICACION1500_HPP
#define INC_1942OLDENAIT_POWERUPBONIFICACION1500_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/default.hpp"
#include "disparo.hpp"
#include "powerUp.hpp"

using namespace std;

class PowerUpBonificacion1500: public PowerUp {
public:
		PowerUpBonificacion1500(float posX, float posY, int valor);
    ~PowerUpBonificacion1500();
		void colisionar();
		void animar(float timeStep);
};

#endif //INC_1942OLDENAIT_POWERUPBONIFICACION1500_HPP
