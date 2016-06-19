#ifndef INC_1942OLDENAIT_ENEMIGOPEQUENIO_HPP
#define INC_1942OLDENAIT_ENEMIGOPEQUENIO_HPP

#include "enemigoVista.hpp"

class EnemigoPequenio : public EnemigoVista {
public:
    EnemigoPequenio();
    ~EnemigoPequenio();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};


#endif //INC_1942OLDENAIT_ENEMIGOPEQUENIO_HPP
