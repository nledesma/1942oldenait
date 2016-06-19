#ifndef INC_1942OLDENAIT_DISPAROENEMIGOVISTA_HPP
#define INC_1942OLDENAIT_DISPAROENEMIGOVISTA_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "figura.hpp"
#include "../../accesorios/default.hpp"

using namespace std;

struct disparoEnemigo {
    float posX;
    float posY;
};

class DisparoEnemigoVista {

private:
    Figura * figuraDisparo;
    string pathSprite;
public:
    DisparoEnemigoVista();
    ~DisparoEnemigoVista();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, SDL_Renderer * renderer);
    void cerrar();
};
#endif //INC_1942OLDENAIT_DISPAROENEMIGOVISTA_HPP
