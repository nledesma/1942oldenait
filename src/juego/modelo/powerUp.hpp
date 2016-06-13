#ifndef INC_1942OLDENAIT_POWERUP_HPP
#define INC_1942OLDENAIT_POWERUP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include "../../accesorios/codigo.hpp"
#include "disparo.hpp"
#include "../../accesorios/colisiones/colisionable.hpp"

using namespace std;

#define FRECUENCIA_ANIMACION 0.08

class PowerUp {
protected:
    int tipo;
    int valor;
    float posX;
    float posY;
    float posXInicial;
    float posYInicial;
    float contadorTiempoAnimacion = 0;
    int estadoAnimacion;
    pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;
    string idSprite;
    Colisionable * colisionable;
    int tiempoPowerUpColisionado;

public:
    virtual ~PowerUp();
    virtual void aplicarPowerUp();
    Colisionable* getColisionable();
    void colisionar();
    virtual float getPosicionX();
    float getPosicionY();
    int getEstadoAnimacion();
    int getTipoPowerUp();
    int getValor();
    string getIdSprite();
    int mover(float timeStep, float velocidadY);
    bool animar(float timeStep);
    void volverEstadoInicial();
};

#endif //INC_1942OLDENAIT_POWERUP_HPP
