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
#include "../../accesorios/colisiones/colisionable.hpp"
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
    Colisionable * colisionable;
    int contador;

public:
    virtual ~AvionEnemigo();
    virtual Disparo* disparar() = 0;
    virtual float getVelocidad();
    virtual float getPosicionX();
    virtual float getPosicionY();
    virtual float getAngulo();
    virtual int getEstadoAnimacion();
    virtual int getTipoAvion();
    virtual int mover(float timeStep);
    virtual int getAncho() = 0;
    virtual int getAlto() = 0;
    virtual int getAnchoDisparo();
    virtual int getAltoDisparo();
    virtual string getIdSprite();
    virtual string getIdSpriteDisparos();
    Colisionable* getColisionable();
    virtual void colisionar();
};


#endif //INC_1942OLDENAIT_AVIONENEMIGO_HPP
