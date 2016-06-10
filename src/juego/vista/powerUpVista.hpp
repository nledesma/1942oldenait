#ifndef INC_1942OLDENAIT_POWERUPVISTA_HPP
#define INC_1942OLDENAIT_POWERUPVISTA_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "figura.hpp"
#include "../../accesorios/default.hpp"
#include "../../accesorios/codigo.hpp"

using namespace std;

class PowerUpVista {
protected:
    Figura * figuraPowerUp;
    string pathSprite;
    SDL_Rect clipsAnimacion[8];
    int estadoAnimacion;
public:
    virtual void cargarImagen(SDL_Renderer * renderer);
    virtual void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
    void cerrar();
};

#endif //INC_1942OLDENAIT_POWERUPVISTA_HPP
