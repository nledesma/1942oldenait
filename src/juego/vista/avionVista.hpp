#ifndef INC_1942OLDENAIT_AVIONVISTA_HPP
#define INC_1942OLDENAIT_AVIONVISTA_HPP

#include <string>
#include <cstring>
using namespace std;

class AvionVista {
private:
    float posX;
    float posY;
    int estadoAnimacion;
    Cliente * cliente;
    SDL_Rect clipsAnimacion[6];
    Figura * figuraAvion;
public:
    AvionVista(float posX, float posY, Cliente * cliente);
    ~AvionVista();
    float getPosX();
    void setPosX(float posX);
    float getPosY();
    void setPosY(float posY);
    void manejarEvento(SDL_Event evento);
    int cargarImagen(string path, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void cerrar();
    int getEstadoAnimacion();
    void setEstadoAnimacion(int estadoAnimacion);
    void actualizar(string codigo);
};


#endif //INC_1942OLDENAIT_AVIONVISTA_HPP
