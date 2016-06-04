#ifndef INC_1942OLDENAIT_AVIONENEMIGO_HPP
#define INC_1942OLDENAIT_AVIONENEMIGO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/default.hpp"
#include "trayectoriasEnemigos/trayectoria.hpp"
#include "disparo.hpp"
#include <pthread.h>

class AvionEnemigo {
protected:
    float velocidadDisparos;
    float posX;
    float posY;
    float angulo;
    int estadoAnimacion;
    int tipoAvion;
    float velocidad;
    string idSprite;
    string idSpriteDisparos;
    pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;
    Trayectoria* trayectoria;

public:
    virtual ~AvionEnemigo();
    virtual Disparo* disparar() = 0;
    virtual int getAncho() = 0;
    virtual int getAlto() = 0;
    float getVelocidad();
    float getPosicionX();
    float getPosicionY();
    float getAngulo();
    int getEstadoAnimacion();
    int getTipoAvion();
    int mover(float timeStep);
    int getAnchoDisparo();
    int getAltoDisparo();
    string getIdSprite();
    string getIdSpriteDisparos();
};


#endif //INC_1942OLDENAIT_AVIONENEMIGO_HPP
