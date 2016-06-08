#ifndef INC_1942OLDENAIT_AVIONGRANDE_HPP
#define INC_1942OLDENAIT_AVIONGRANDE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "avionEnemigo.hpp"
#include "trayectoriasEnemigos/trayectoria.hpp"
#include "disparo.hpp"
#include <pthread.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "avionEnemigo.hpp"
#include "trayectoriasEnemigos/trayectoria.hpp"
#include "disparo.hpp"
#include <pthread.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <chrono>
#include "../../accesorios/codigo.hpp"
#include "../../accesorios/trigonomaster.hpp"
#include "trayectoriasEnemigos/trayectoria.hpp"
#include "disparo.hpp"
#include "avionEnemigo.hpp"
#include <pthread.h>
#include <vector>

#define FRECUENCIA_DISPAROS 30
#define ALTURA_INICIO_DISPAROS 300

class AvionGrande: public AvionEnemigo {
private:
    float contadorTimesteps = 0;
public:
    AvionGrande(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria);
    ~AvionGrande();
    int getAncho();
    int getAlto();
    bool correspondeDisparar(float timestep);
    vector<DisparoEnemigo*> disparar();
};

#endif //INC_1942OLDENAIT_AVIONGRANDE_HPP
