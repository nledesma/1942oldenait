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
    int vidas = 1;
    string idSprite;
    string idSpriteDisparos;
    pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;
    Trayectoria* trayectoria;
    Colisionable * colisionable;
    int contador;
    int valorImpacto;
    int valorDerribo;

public:
    virtual ~AvionEnemigo();
    int getAncho();
    int getAlto();
    float getVelocidad();
    float getPosicionX();
    float getPosicionY();
    float getAngulo();
    int getEstadoAnimacion();
    int getTipoAvion();
    virtual int mover(float timeStep);
    int getAnchoDisparo();
    int getAltoDisparo();
    string getIdSprite();
    string getIdSpriteDisparos();
    Colisionable* getColisionable();
    virtual void colisionar();
    DisparoEnemigo* disparar(float xObjetivo, float yObjetivo);
    virtual bool correspondeDisparar(float timestep) = 0;
    virtual vector<DisparoEnemigo*> disparar() = 0;
    void setVidasEnUno();
    virtual int estallar();
    virtual bool estaColisionando();
};


#endif //INC_1942OLDENAIT_AVIONENEMIGO_HPP
