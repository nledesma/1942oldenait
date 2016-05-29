#ifndef INC_1942OLDENAIT_ENEMIGOMEDIANO_HPP
#define INC_1942OLDENAIT_ENEMIGOMEDIANO_HPP

#include "enemigoVista.hpp"

class EnemigoMediano : public EnemigoVista {
public:
    EnemigoMediano();
    ~EnemigoMediano();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};


#endif //INC_1942OLDENAIT_ENEMIGOMEDIANO_HPP
