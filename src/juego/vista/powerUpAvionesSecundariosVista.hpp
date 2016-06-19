#ifndef INC_1942OLDENAIT_POWERUP_AVIONES_SECUNDARIOS_VISTA_HPP
#define INC_1942OLDENAIT_POWERUP_AVIONES_SECUNDARIOS_VISTA_HPP

#include "powerUpVista.hpp"
#include "../../accesorios/codigo.hpp"

class PowerUpAvionesSecundariosVista : public PowerUpVista {
public:
    PowerUpAvionesSecundariosVista();
    ~PowerUpAvionesSecundariosVista();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};

#endif //INC_1942OLDENAIT_POWERUP_AVIONES_SECUNDARIOS_VISTA_HPP