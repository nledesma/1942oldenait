#ifndef INC_1942OLDENAIT_AVIONVISTA_HPP
#define INC_1942OLDENAIT_AVIONVISTA_HPP

#include <string>
#include <cstring>
#include "figura.hpp"
#include "../../accesorios/codigo.hpp"
#include "../../net/decodificador.hpp"
#include "../../accesorios/default.hpp"
#include "avionSecundarioVista.hpp"

using namespace std;

class AvionVista {
private:
    float posX;
    float posY;
    string pathSprite;
    int estadoAnimacion;
    SDL_Rect clipsAnimacion[32];
    pthread_mutex_t mutexActualizar = PTHREAD_MUTEX_INITIALIZER;
    Figura *figura;
    void iniciarAvion(float posX, float posY , string pathSprite, int estadoPowerUP);
    int vidas;
    int estadoPowerUP;

public:
    AvionVista(float posX, float posY, string pathSprite,  int estadoPowerUP);

    AvionVista(string infoAvion);

    ~AvionVista();

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

    int getEstadoPowerUp();

    void setPosX(float posX);

    void setPosY(float posY);

    void setFigura(Figura *figura);

    void setEstadoAnimacion(int estadoAnimacion);

    int actualizar(string codigo);

    void cerrar();

};


#endif //INC_1942OLDENAIT_AVIONVISTA_HPP
