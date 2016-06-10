#ifndef INC_1942OLDENAIT_DISPAROENEMIGO_HPP
#define INC_1942OLDENAIT_DISPAROENEMIGO_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <pthread.h>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/colisiones/colisionable.hpp"
using namespace std;

class DisparoEnemigo {
private:
    float velocidad;
    float versorX;
    float versorY;
    float posX;
    float posY;
    int nroAvionDisparador;
    pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;
    Colisionable* colisionable;
    bool colisiono;
public:
    DisparoEnemigo(float posX, float posY, float velocidad,float versorX, float versorY);
    ~DisparoEnemigo();
    void setVelocidad(float velocidad);
    float getVelocidad();
    int mover(float timeStep);
    void setPosY(float posY);
    float getPosY();
    void setPosX(float posX);
    float getPosX();
    int getAlto();
    int getAncho();
    void setAvion(int nroAvion);
    int getNroAvion();
    Colisionable* getColisionable();
    void colisionar();
};

#endif //INC_1942OLDENAIT_DISPAROENEMIGO_HPP
