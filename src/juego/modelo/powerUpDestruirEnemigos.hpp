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
		void colisionar();
		void animar(float timeStep);
};

#endif //INC_1942OLDENAIT_POWERUPDESTRUIRENEMIGOS_HPP
