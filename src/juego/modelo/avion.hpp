#ifndef INC_1942OLDENAIT_AVION_HPP
#define INC_1942OLDENAIT_AVION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/colisiones/colisionable.hpp"
#include "disparo.hpp"
#include <pthread.h>

#define AVION_ANCHO ANCHO_AVION_COMUN;
#define AVION_ALTO ALTO_AVION_COMUN;
#define DISPARO_ANCHO 20;
#define DISPARO_ALTO 40;
#define TIEMPO_INMUNIDAD 3
#define TIEMPO_INTERMITENCIA 0.1
using namespace std;

class Avion {
private:
    float contadorTiempoInmunidad = 0;
    float contadorIntermitenciaInmunidad = 0;
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
    float posXFinal;
    float posYFinal;
    int puntaje;
    string idSprite;
    string idSpriteDisparos;
    pthread_mutex_t mutexMover = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexVidas = PTHREAD_MUTEX_INITIALIZER;
    Colisionable* colisionable;
    int vidas;

public:
    Avion(float posX, float posY, float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos, float posXFinal = 0, float posYFinal = 0);

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

    void volverEstadoInicial(bool inmunidad = true);

    string getIdSprite();

    string getIdSpriteDisparos();

    void setPosicion(float x, float y);

    void sumarPuntos(int puntos);

    Colisionable * getColisionable();

    void colisionar();

    void colisionarConPowerUp();

    void resetPuntos();

    int getPuntaje();

    int getVidas();

    void setSpawn(int x, int y);

    void quitarUnaVida();

    void disminuirTiempoInmunidad(float timestep);

    float getContadorTiempoInmunidad();

    bool moverAPosicionFinal(float timestep);
};

#endif //INC_1942OLDENAIT_AVION_HPP
