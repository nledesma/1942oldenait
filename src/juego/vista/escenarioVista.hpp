#ifndef INC_1942OLDENAIT_ESCENARIOVISTA_HPP
#define INC_1942OLDENAIT_ESCENARIOVISTA_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include "ventana.hpp"
#include "avionVista.hpp"
#include "figura.hpp"
#include "elementoVista.hpp"
#include "disparoVista.hpp"
#include "../../accesorios/temporizador.hpp"
#include <list>
#include <iterator>
#include <pthread.h>

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
    DisparoVista* disparoVista;
    list<disparo> disparos;
    Figura *fondo;
    bool activo = false;

public:
    /* Constructor y destructor */
    EscenarioVista(int ancho, int alto, string pathImagen);
    ~EscenarioVista();
    void cargarFondo();
    void cargarAvion(AvionVista* avionVista, SDL_Renderer* renderer, int numeroJugador);
    void cargarElemento(ElementoVista *elemento, SDL_Renderer *renderer);
    int iniciar(pthread_mutex_t mutexEscritura);
    void setActivo();
    void setInactivo();
    void setDisparos(list<disparo> disparos);
    int getAncho();
    int getAlto();
    float getScrollingOffset();
    void setScrollingOffset(float scrollingOffset);
    //Ventana* getVentana();
    list<AvionVista *> &getAviones();
    list<ElementoVista *> &getElementos();
    void agregarAvionVista(float posX, float posY, string pathSprite);
    void agregarElementoVista(float posX, float posY, string elementoSpriteId);
    void agregarDisparoVista(string pathSprite);
    void renderizarAviones(pthread_mutex_t mutexEscritura);
    void renderizarElementos(pthread_mutex_t mutexEscritura);
    void renderizarFondo(float y);
    void renderizarDisparos(pthread_mutex_t mutexEscritura);
    Figura *getFondo();
    Ventana *getVentana();
    void cargarVistasAviones();
    void cargarVistasElementos();
    void actualizar(string codigo);
    void iniciarEscenario(string infoEscenario);
    void crearEscenario(string infoEscenario);
};

#endif //INC_1942OLDENAIT_ESCENARIOVISTA_HPP
