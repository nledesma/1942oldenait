#ifndef INC_1942OLDENAIT_AVIONMEDIANO_HPP
#define INC_1942OLDENAIT_AVIONMEDIANO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "avionEnemigo.hpp"
#include "trayectoriasEnemigos/trayectoria.hpp"
#include "disparo.hpp"
#include <pthread.h>

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

class AvionMediano: public AvionEnemigo {
public:
    AvionMediano(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria);
    ~AvionMediano();
    Disparo* disparar();
    int getAncho();
    int getAlto();
};

#endif //INC_1942OLDENAIT_AVIONMEDIANO_HPP
