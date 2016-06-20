#ifndef INC_1942OLDENAIT_AVION_SECUNDARIO_HPP
#define INC_1942OLDENAIT_AVION_SECUNDARIO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/default.hpp"
#include "../../accesorios/colisiones/colisionable.hpp"
#include "disparo.hpp"
#include <pthread.h>

#define AVION_SECUNDARIO_ANCHO ANCHO_AVION_SECUNDARIO;
#define AVION_SECUNDARIO_ALTO ALTO_AVION_SECUNDARIO;
#define DISPARO_ANCHO 20;
#define DISPARO_ALTO 40;
using namespace std;

class AvionSecundario {
private:
    float velocidadDisparos;
    float posX;
    float posY;
    float velocidadX;
    float velocidadY;
    int estadoAnimacion;
    float velocidad;
    float posXInicial;
    float posYInicial;
    float posXFinal;
    float posYFinal;
    int puntaje;
    string idSprite = SPRITE_AVION_SECUNDARIO;
    string idSpriteDisparos;
    pthread_mutex_t mutexMoverAvionSecundario = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexPuntaje = PTHREAD_MUTEX_INITIALIZER;
    Colisionable* colisionable;
    int cantidadDisparos = 0;
    int cantidadAciertos = 0;

public:
    AvionSecundario(float posX, float posY, float velocidad, float velocidadDisparos, string idSpriteDisparos, float posXFinal = 0, float posYFinal = 0);

    ~AvionSecundario();

    void manejarEvento(int evento);

    vector<Disparo*> disparar();

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

    Colisionable * getColisionable();

    void colisionar();

    void colisionarConPowerUp();

    void resetPuntos();


    int getPuntaje();

    void setSpawn(int x, int y);

    bool moverAPosicionFinal(float timestep);

    bool estaColisionando();

    //TODO revisar como mandar los puntos al avion original.
    int getCantidadDisparos();

    void aumentarAciertos();

    int getCantidadAciertos();

    int getPorcentajeAciertos();

    void sumarPuntos(int puntos);
};

#endif //INC_1942OLDENAIT_AVION_HPP
