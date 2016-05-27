#ifndef INC_1942OLDENAIT_AVIONGRANDE_HPP
#define INC_1942OLDENAIT_AVIONGRANDE_HPP

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

class AvionGrande: public AvionEnemigo {
private:
    float velocidadDisparos;
    float posX;
    float posY;
    float velocidadX;
    float velocidadY;
    float angulo;
    int estadoAnimacion;
    float velocidad;
    float posXInicial;
    float posYInicial;
    string idSprite;
    string idSpriteDisparos;
    pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;
    Trayectoria trayectoria;

public:
    AvionGrande(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, string idSprite, string idSpriteDisparos, Trayectoria trayectoria);

    ~AvionGrande();

    Disparo* disparar();

    void mover(float timeStep);

    void volverEstadoInicial();
};

#endif //INC_1942OLDENAIT_AVIONGRANDE_HPP
