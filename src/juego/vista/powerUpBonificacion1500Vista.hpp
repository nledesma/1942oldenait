#ifndef INC_1942OLDENAIT_POWERUP_BONIFICACION_1500_VISTA_HPP
#define INC_1942OLDENAIT_POWERUP_BONIFICACION_1500_VISTA_HPP

#include "powerUpVista.hpp"

class PowerUpBonificacion1500Vista : public PowerUpVista {
public:
    PowerUpBonificacion1500Vista();
    ~PowerUpBonificacion1500Vista();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};


#endif //INC_1942OLDENAIT_POWERUP_BONIFICACION_1500_VISTA_HPP
