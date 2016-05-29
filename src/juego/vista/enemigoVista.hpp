#ifndef INC_1942OLDENAIT_ENEMIGOVISTA_HPP
#define INC_1942OLDENAIT_ENEMIGOVISTA_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "figura.hpp"
#include "../../accesorios/default.hpp"
#include "../../accesorios/codigo.hpp"

using namespace std;

class EnemigoVista {
protected:
    Figura * figuraEnemigo;
    string pathSprite;
    SDL_Rect clipsAnimacion[28];
    int estadoAnimacion;
public:
    virtual void cargarImagen(SDL_Renderer * renderer);
    virtual void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
    void cerrar();
};

#endif //INC_1942OLDENAIT_ENEMIGOVISTA_HPP
