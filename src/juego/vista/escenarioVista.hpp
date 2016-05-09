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
    pthread_mutex_t mutexActualizar = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexDisparos = PTHREAD_MUTEX_INITIALIZER;

public:
    /* Constructor y destructor */
    EscenarioVista(string infoEscenario);
    void inicializarComponentes(string infoEscenario);
    void actualizarComponentes(string infoActualizacion);
    ~EscenarioVista();
    void cargarFondo();
    void cargarAvion(AvionVista* avionVista, SDL_Renderer* renderer, int numeroJugador);
    void cargarElemento(ElementoVista *elemento, SDL_Renderer *renderer);
    int mainLoop();
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
    void agregarAvionVista(string infoAvion);
    void agregarElementoVista(string codigo);
    void agregarDisparoVista(string pathSprite);
    void renderizarAviones();
    void renderizarElementos();
    void renderizarFondo(float y);
    void renderizarDisparos();
    Figura *getFondo();
    Ventana *getVentana();
    void cargarVistasAviones();
    void cargarVistasElementos();
    void actualizar(float offset);
};

#endif //INC_1942OLDENAIT_ESCENARIOVISTA_HPP
