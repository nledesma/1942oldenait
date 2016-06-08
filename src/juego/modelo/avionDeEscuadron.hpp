#ifndef INC_1942OLDENAIT_AVIONDEESCUADRON_HPP
#define INC_1942OLDENAIT_AVIONDEESCUADRON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "disparo.hpp"
#include "avionEnemigo.hpp"
#include "trayectoriasEnemigos/trayectoria.hpp"
#include <pthread.h>

class AvionDeEscuadron: public AvionEnemigo {
public:
    AvionDeEscuadron(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria);
    ~AvionDeEscuadron();
    int getAncho();
    int getAlto();
};

#endif //INC_1942OLDENAIT_AVIONDEESCUADRON_HPP
