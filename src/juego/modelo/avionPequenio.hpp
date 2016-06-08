#ifndef INC_1942OLDENAIT_AVIONPEQUENIO_HPP
#define INC_1942OLDENAIT_AVIONPEQUENIO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/trigonomaster.hpp"
#include "trayectoriasEnemigos/trayectoria.hpp"
#include "disparo.hpp"
#include "avionEnemigo.hpp"
#include <pthread.h>

class AvionPequenio: public AvionEnemigo {
public:
    AvionPequenio(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria);
    ~AvionPequenio();
    int getAncho();
    int getAlto();
};

#endif //INC_1942OLDENAIT_AVIONPEQUENIO_HPP
