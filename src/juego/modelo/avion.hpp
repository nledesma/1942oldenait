#ifndef INC_1942OLDENAIT_AVION_HPP
#define INC_1942OLDENAIT_AVION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "escenarioJuego.hpp"
#include "disparo.hpp"

//TODO estas constantes estaban definidas para el tuto.
#define SCREEN_WIDTH = 800;
#define SCREEN_HEIGHT = 800;
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
    EscenarioJuego escenarioJuego;

public:
    static const int AVION_ANCHO = ANCHO_AVION_COMUN;
    static const int AVION_ALTO = ALTO_AVION_COMUN;
    static const int DISPARO_ANCHO = 20;
    static const int DISPARO_ALTO = 40;

    Avion(float posX, float posY, float velocidad, float velocidadDisparos);

    ~Avion();

    void manejarEvento(int evento);

    void disparar();

    float getVelocidad();

    float getVelocidadX();

    float getVelocidadY();

    float getPosicionX();

    float getPosicionY();

    EscenarioJuego *getEscenarioJuego();

    int getEstadoAnimacion();

    void setVelocidad();

    void setVelocidadX();

    void setVelocidadY();

    void setPosicionX();

    void setPosicionY();

    void setEscenarioJuego(EscenarioJuego *escenarioJuego);

    void mover(float timeStep);

    int getAncho();

    int getAlto();

    int getAnchoDisparo();

    int getAltoDisparo();

    void loop();
};

#endif //INC_1942OLDENAIT_AVION_HPP
