#ifndef DISPARO_VISTA_HPP
#define DISPARO_VISTA_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "figura.hpp"
#include "../../accesorios/default.hpp"

using namespace std;

struct disparo {
    float posX;
    float posY;
    int estado;
};

class DisparoVista {

private:
    Figura * figuraDisparo;
    string pathSprite;
    SDL_Rect clipsAnimacion[2];

public:
    DisparoVista(string pathSprite);
    ~DisparoVista();

    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estado,SDL_Renderer * renderer);
    void cerrar();
};
#endif
