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
    AvionDeEscuadron(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, string idSprite, string idSpriteDisparos, Trayectoria trayectoria);

    ~AvionDeEscuadron();

    Disparo* disparar();

    void mover(float timeStep);

    void volverEstadoInicial();
};

#endif //INC_1942OLDENAIT_AVIONDEESCUADRON_HPP
