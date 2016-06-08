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
#include "disparoEnemigo.hpp"
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
    Colisionable* getColisionable();
    virtual void colisionar();
    DisparoEnemigo* disparar(float xObjetivo, float yObjetivo);
    virtual vector<DisparoEnemigo*> disparar() = 0;
};


#endif //INC_1942OLDENAIT_AVIONENEMIGO_HPP
