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
};

class DisparoVista {

private:
    Figura * figuraDisparo;
    string pathSprite;
public:
    DisparoVista(string pathSprite);
    ~DisparoVista();

    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, SDL_Renderer * renderer);
    void cerrar();
};
#endif
