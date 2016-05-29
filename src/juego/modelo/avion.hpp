#ifndef INC_1942OLDENAIT_AVION_HPP
#define INC_1942OLDENAIT_AVION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "disparo.hpp"
#include <pthread.h>

#define AVION_ANCHO ANCHO_AVION_COMUN;
#define AVION_ALTO ALTO_AVION_COMUN;
#define DISPARO_ANCHO 20;
#define DISPARO_ALTO 40;
using namespace std;

class Avion {
private:
    float velocidadDisparos;
    float posX;
    float posY;
    float velocidadX;
    float velocidadY;
    int estadoAnimacion;
    float velocidad;
    int contador;
    float posXInicial;
    float posYInicial;
    string idSprite;
    string idSpriteDisparos;
    pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;

public:
    Avion(float posX, float posY, float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos);

    ~Avion();

    void manejarEvento(int evento);

    Disparo* disparar();

    float getVelocidad();

    float getPosicionX();

    float getPosicionY();

    int getEstadoAnimacion();

    void setVelocidad(float velocidad);

    void setEstadoAnimacion(int estadoAnimacion);

    void mover(float timeStep);

    int getAncho();

    int getAlto();

    int getAnchoDisparo();

    int getAltoDisparo();

    void volverEstadoInicial();

    string getIdSprite();

    string getIdSpriteDisparos();

    void setPosicion(float x, float y);
};

#endif //INC_1942OLDENAIT_AVION_HPP
