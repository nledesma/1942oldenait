#ifndef VENTANA_HPP
#define VENTANA_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "figura.hpp"

using namespace std;

class Ventana {
private:
    int ancho;
    int alto;
    SDL_Window *sdlWindow = NULL;
    SDL_Renderer *gVentanaRenderer = NULL;

public:
    /* Constructor */
    Ventana(int ancho, int alto);

    /* Inicializa la ventana */
    int iniciar();

    /* Cierra la ventana */
    void cerrar();

    int getAncho();

    void setAncho(int ancho);

    int getAlto();

    void setAlto(int alto);

    /* Retorna el renderer de la ventana */
    SDL_Renderer *getVentanaRenderer();

    /* Retorna la ventana de SDL */
    SDL_Window *getSdlWindow();
};

#endif //INC_1942OLDENAIT_VENTANA_HPP
