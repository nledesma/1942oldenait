#ifndef DISPARO_AVION_SECUNDARIO_VISTA_HPP
#define DISPARO_AVION_SECUNDARIO_VISTA_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "figura.hpp"
#include "../../accesorios/default.hpp"

using namespace std;

struct disparoAvionSecundario {
    float posX;
    float posY;
    int estado;
};

class DisparoAvionSecundarioVista {

private:
    Figura * figuraDisparo;
    string pathSprite;
    SDL_Rect clipsAnimacion[2];

public:
    DisparoAvionSecundarioVista(string pathSprite);
    ~DisparoAvionSecundarioVista();

    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estado,SDL_Renderer * renderer);
    void cerrar();
};
#endif
