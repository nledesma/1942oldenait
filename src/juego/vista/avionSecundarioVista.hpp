#ifndef INC_1942OLDENAIT_AVION_SECUNDARIO_VISTA_HPP
#define INC_1942OLDENAIT_AVION_SECUNDARIO_VISTA_HPP

#include <string>
#include <cstring>
#include "figura.hpp"
#include "../../accesorios/codigo.hpp"
#include "../../net/decodificador.hpp"
#include "../../accesorios/default.hpp"

using namespace std;

class AvionSecundarioVista {
private:
    float posX;
    float posY;
    string pathSprite;
    int estadoAnimacion;
    SDL_Rect clipsAnimacion[14];
    pthread_mutex_t mutexActualizarAvionesSecundarios = PTHREAD_MUTEX_INITIALIZER;
    Figura *figura;
    void iniciarAvion(float posX, float posY);
public:
    AvionSecundarioVista(float posX, float posY);

    AvionSecundarioVista(string infoAvion);

    ~AvionSecundarioVista();

    void manejarEvento(SDL_Event evento);

    void cargarImagen(SDL_Renderer *renderer, int color = BASE);

    void render(SDL_Renderer *renderer);

    int getEstadoAnimacion();

    Figura *getFigura();

    float getPosX();

    float getPosY();

    int getVidas();

    int getAncho();

    int getAlto();

    void setPosX(float posX);

    void setPosY(float posY);

    void setFigura(Figura *figura);

    void setEstadoAnimacion(int estadoAnimacion);

    int actualizar(string codigo);

    void cerrar();

    void cargarAvionSecundario(SDL_Renderer* renderer);

};


#endif //INC_1942OLDENAIT_AVION_SECUNDARIO_VISTA_HPP
