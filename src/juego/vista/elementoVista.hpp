#ifndef INC_1942OLDENAIT_ELEMENTOVISTA_HPP
#define INC_1942OLDENAIT_ELEMENTOVISTA_HPP

#include <string>
#include <cstring>
#include <SDL2/SDL.h>
#include "figura.hpp"

using namespace std;

class ElementoVista {
    float posX;
    float posY;
    string pathSprite;
    Figura* figura;
    static const string ELEMENTO_POR_DEFECTO = "../../../resources/img/planeta.bmp";

public:
    ElementoVista(float posX, float posY, string pathSprite);
    void actualizar(string codigo);
    void render(SDL_Renderer* renderer);
    void cargarImagen(SDL_Renderer* renderer);
    float getPosX();
    float getPosY();

};

#endif //INC_1942OLDENAIT_ELEMENTOVISTA_HPP
