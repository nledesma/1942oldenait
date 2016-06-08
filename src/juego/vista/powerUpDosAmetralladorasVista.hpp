#ifndef INC_1942OLDENAIT_POWERUP_DOS_AMETRALLADORAS_VISTA_HPP
#define INC_1942OLDENAIT_POWERUP_DOS_AMETRALLADORAS_VISTA_HPP

#include "powerUpVista.hpp"

class PowerUpDosAmetralladorasVista : public EnemigoVista {
public:
    PowerUpDosAmetralladorasVista();
    ~PowerUpDosAmetralladorasVista();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};

#endif //INC_1942OLDENAIT_POWERUP_DOS_AMETRALLADORAS_VISTA_HPP