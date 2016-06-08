#ifndef INC_1942OLDENAIT_POWERUP_BONIFICACION_VISTA_HPP
#define INC_1942OLDENAIT_POWERUP_BONIFICACION_VISTA_HPP

#include "powerUpVista.hpp"

class PowerUpBonificacionVista : public EnemigoVista {
public:
    PowerUpBonificacionVista();
    ~PowerUpBonificacionVista();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};


#endif //INC_1942OLDENAIT_POWERUP_BONIFICACION_VISTA_HPP
