#ifndef INC_1942OLDENAIT_AVIONVISTA_HPP
#define INC_1942OLDENAIT_AVIONVISTA_HPP

#include <string>
#include <cstring>
#include "figura.hpp"
#include "../../accesorios/codigo.hpp"
#include "../../net/decodificador.hpp"

#define AVION_POR_DEFECTO "imagen-default"

using namespace std;

class AvionVista {
private:
    float posX;
    float posY;
    string pathSprite;
    int estadoAnimacion;
    SDL_Rect clipsAnimacion[6];
    pthread_mutex_t mutexActualizar = PTHREAD_MUTEX_INITIALIZER;
    Figura *figura;
    void iniciarAvion(float poX, float posY, string pathSprite);
public:
    AvionVista(float posX, float posY, string pathSprite);

    AvionVista(string infoAvion);

    ~AvionVista();

    void manejarEvento(SDL_Event evento);

    void cargarImagen(SDL_Renderer *renderer, int color = BASE);

    void render(SDL_Renderer *renderer);

    int getEstadoAnimacion();

    Figura *getFigura();

    float getPosX();

    float getPosY();

    int getAncho();

    int getAlto();

    void setPosX(float posX);

    void setPosY(float posY);

    void setFigura(Figura *figura);

    void setEstadoAnimacion(int estadoAnimacion);

    void actualizar(string codigo);

    void cerrar();
};


#endif //INC_1942OLDENAIT_AVIONVISTA_HPP
