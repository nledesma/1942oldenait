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

class EscenarioVista {
private:
    int ancho;
    int alto;
    float scrollingOffset;
    string pathImagen;
    Ventana *ventana;
    list<AvionVista *> aviones;
    list<ElementoVista *> elementos;
    Figura *fondo;

public:
    /* Constructor y destructor */
    EscenarioVista(int ancho, int alto, string pathImagen);
    ~EscenarioVista();

    void cargarFondo();

    void cargarAvion(AvionVista* avionVista, SDL_Renderer* renderer, int numeroJugador);

    void cargarElemento(ElementoVista *elemento, SDL_Renderer *renderer);

    int iniciar();

    int getAncho();

    int getAlto();

    //Ventana* getVentana();
    list<AvionVista *> &getAviones();

    list<ElementoVista *> &getElementos();

    void agregarAvionVista(float posX, float posY, string pathSprite);

    void agregarElementoVista(float posX, float posY, string elementoSpriteId);

    void renderizarAviones();

    void renderizarElementos();

    void renderizarFondo(float y);

    Figura *getFondo();

    Ventana *getVentana();

    void cargarVistasAviones();

    void cargarVistasElementos();
};

#endif //INC_1942OLDENAIT_ESCENARIOVISTA_HPP
