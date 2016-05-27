#ifndef INC_1942OLDENAIT_AVIONMEDIANO_HPP
#define INC_1942OLDENAIT_AVIONMEDIANO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "avionEnemigo.hpp"
#include "trayectoria.hpp"
#include "disparo.hpp"
#include <pthread.h>

class AvionMediano: public avionEnemigo {
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
    AvionMediano(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, string idSprite, string idSpriteDisparos, Trayectoria trayectoria);

    ~AvionMediano();

    Disparo* disparar();

    void mover(float timeStep);

    void volverEstadoInicial();
};

#endif //INC_1942OLDENAIT_AVIONMEDIANO_HPP
