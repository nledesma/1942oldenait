#ifndef INC_1942OLDENAIT_AVIONVISTA_HPP
#define INC_1942OLDENAIT_AVIONVISTA_HPP

#include <string>
#include <cstring>
#include "figura.hpp"
#include "../../accesorios/codigo.hpp"

#define AVION_POR_DEFECTO "../../../resources/img/millenium-sprite.bmp"

using namespace std;

class AvionVista {
private:
    float posX;
    float posY;
    string pathSprite;
    int estadoAnimacion;
    SDL_Rect clipsAnimacion[6];
    Figura *figura;
public:
    AvionVista(float posX, float posY, string pathSprite);

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
