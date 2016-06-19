#ifndef INC_1942OLDENAIT_ENEMIGODEESCUADRON_HPP
#define INC_1942OLDENAIT_ENEMIGODEESCUADRON_HPP


#include "enemigoVista.hpp"

class EnemigoDeEscuadron : public EnemigoVista {
public:
    EnemigoDeEscuadron();
    ~EnemigoDeEscuadron();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};



#endif //INC_1942OLDENAIT_ENEMIGODEESCUADRON_HPP
