#ifndef INC_1942OLDENAIT_ELEMENTOVISTA_HPP
#define INC_1942OLDENAIT_ELEMENTOVISTA_HPP

#include <string>
#include <cstring>
#include <SDL2/SDL.h>

using namespace std;

class ElementoVista {
    int id;
    float posX;
    float posY;
public:
    ElementoVista(int id, float posX, float posY);
    void actualizar(string codigo);
    //void render(SDL_Renderer* renderer);

    float getPosX();
    float getPosY();

};

#endif //INC_1942OLDENAIT_ELEMENTOVISTA_HPP
