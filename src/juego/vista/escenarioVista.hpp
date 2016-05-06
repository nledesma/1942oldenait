#ifndef INC_1942OLDENAIT_ESCENARIOVISTA_HPP
#define INC_1942OLDENAIT_ESCENARIOVISTA_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "ventana.hpp"
#include "avionVista.hpp"
#include "figura.hpp"
#include "../../accesorios/temporizador.hpp"
#include "elementoVista.hpp"
#include <list>
#include <iterator>

using namespace std;
struct fondo {
    string imagenFondo;
    int ancho;
    int alto;
};

class EscenarioVista {
private:
    int ancho;
    int alto;
    float scrollingOffset;
    Ventana *ventana;
    list<AvionVista *> aviones;
    list<ElementoVista *> elementos;
    Figura *fondo;

public:
    /* Constructor y destructor */
    EscenarioVista(int ancho, int alto);
    ~EscenarioVista();

    bool cargarImagenDeFondo(SDL_Renderer *renderer);

    void cargarAvion(Avion *avion, SDL_Renderer *renderer, string path);

    void cargarElemento(Elemento *elemento, SDL_Renderer *renderer, string path);

    int iniciar(string path);

    int getAncho();

    int getAlto();

    float getVelocidadDesplazamientoY();

    //Ventana* getVentana();
    list<Avion *> &getAviones();

    list<Elemento *> &getElementos();

    void agregarAvionVista(string avionSpriteId, string disparosSpriteId);

    void agregarElementoVista(string spriteId, float posX, float posY);

    void renderizarVistasAviones(SDL_Renderer *renderer);

    void renderizarVistasElementos(SDL_Renderer *renderer);

    Figura *getFondo();

    Avion *getAvion();

    Ventana *getVentana();

    const char *getFondoSprite();

    int getAnchoFondo();

    int getAltoFondo();

    void incluirAviones();

    void incluirElementos();
};

#endif //INC_1942OLDENAIT_ESCENARIOVISTA_HPP
