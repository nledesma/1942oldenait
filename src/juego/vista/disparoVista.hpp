#ifndef DISPARO_HPP
#define DISPARO_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "figura.hpp"

using namespace std;

struct disparo {
    float posX;
    float posY;
};

class DisparoVista {

private:
    Figura * figuraDisparo;
    string pathSprite;
    static const string DISPARO_POR_DEFECTO = "../../../resources/img/redLaserRay.bmp";
public:
    DisparoVista(string pathSprite);
    ~DisparoVista();

    int cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, SDL_Renderer * renderer);
};
#endif
