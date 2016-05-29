#ifndef INC_1942OLDENAIT_ENEMIGOGRANDE_HPP
#define INC_1942OLDENAIT_ENEMIGOGRANDE_HPP

#include "enemigoVista.hpp"

class EnemigoGrande : public EnemigoVista {
public:
    EnemigoGrande();
    ~EnemigoGrande();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};

#endif //INC_1942OLDENAIT_ENEMIGOGRANDE_HPP
