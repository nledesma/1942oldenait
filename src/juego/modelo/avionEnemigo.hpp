#ifndef INC_1942OLDENAIT_AVIONENEMIGO_HPP
#define INC_1942OLDENAIT_AVIONENEMIGO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "trayectoria.hpp"
#include "disparo.hpp"
#include <pthread.h>

class AvionEnemigo {
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
    AvionEnemigo(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, string idSprite, string idSpriteDisparos, Trayectoria trayectoria);

    ~AvionEnemigo();

    Disparo* disparar();

    float getVelocidad();

    float getPosicionX();

    float getPosicionY();

    float getAngulo();

    int getEstadoAnimacion();

    void setVelocidad(float velocidad);

    void setVelocidadX();

    void setVelocidadY();

    void setPosicionX();

    void setPosicionY();

    void setEstadoAnimacion(int estadoAnimacion);

    void mover(float timeStep);

    int getAncho();

    int getAlto();

    int getAnchoDisparo();

    int getAltoDisparo();

    void volverEstadoInicial();

    string getIdSprite();

    string getIdSpriteDisparos();
};


#endif //INC_1942OLDENAIT_AVIONENEMIGO_HPP
