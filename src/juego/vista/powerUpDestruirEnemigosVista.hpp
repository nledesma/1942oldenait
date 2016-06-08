#ifndef INC_1942OLDENAIT_POWERUP_DESTRUIR_ENEMIGOS_VISTA_HPP
#define INC_1942OLDENAIT_POWERUP_DESTRUIR_ENEMIGOS_VISTA_HPP

#include "powerUpVista.hpp"

class PowerUpDestruirEnemigosVista : public EnemigoVista {
public:
    PowerUpDestruirEnemigosVista();
    ~PowerUpDestruirEnemigosVista();
    void cargarImagen(SDL_Renderer * renderer);
    void render(float posX, float posY, int estadoAnimacion, SDL_Renderer * renderer);
};


#endif //INC_1942OLDENAIT_POWERUP_DESTRUIR_ENEMIGOS_VISTA_HPP
