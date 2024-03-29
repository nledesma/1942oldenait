#ifndef INC_1942OLDENAIT_ELEMENTOVISTA_HPP
#define INC_1942OLDENAIT_ELEMENTOVISTA_HPP

#include <string>
#include <cstring>
#include <SDL2/SDL.h>
#include "figura.hpp"
#include "../../net/decodificador.hpp"
#include "../../accesorios/default.hpp"
#include <pthread.h>

using namespace std;

class ElementoVista {
private:
    float posX;
    float posY;
    string pathSprite;
    Figura* figura;
    pthread_mutex_t mutexActualizar = PTHREAD_MUTEX_INITIALIZER;
public:
    ElementoVista(string codigo);
    ElementoVista(float posX, float posY, string pathSprite);
    ~ElementoVista();
    void actualizar(string codigo);
    void render(SDL_Renderer* renderer);
    void cargarImagen(SDL_Renderer* renderer);
    void cerrar();
    float getPosX();
    float getPosY();

};

#endif //INC_1942OLDENAIT_ELEMENTOVISTA_HPP
