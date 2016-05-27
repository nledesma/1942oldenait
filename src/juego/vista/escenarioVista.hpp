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
#include "etapaVista.hpp"
#include "disparoVista.hpp"
#include "../../accesorios/colaConcurrente/colaConcurrente.hpp"
#include "../../accesorios/temporizador.hpp"
#include <list>
#include <iterator>
#include <pthread.h>
#include "../../accesorios/default.hpp"

using namespace std;

class EscenarioVista {
private:
    /* Fondo */
    int ancho;
    int alto;
    float scrollingOffset;
    string pathImagen;
    Figura *fondo;
    /* Ventana */
    int anchoVentana;
    int altoVentana;
    Ventana *ventana;
    list<AvionVista *> aviones;
    list<ElementoVista *> elementos;
    DisparoVista* disparoVista;
    list<disparo> disparos;
    /* Etapas */
    list<EtapaVista*> etapas;
    list<EtapaVista*>::iterator itEtapa;
    /* Estado */
    bool activo = false;
    /* Sincronización */
    pthread_mutex_t mutexActualizar = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexDisparos = PTHREAD_MUTEX_INITIALIZER;
    ColaConcurrente <int> colaEventos;

public:
    /* Constructor y destructor */
    EscenarioVista(string infoEscenario);
    void inicializarComponentes(string infoEscenario);
    void actualizarComponentes(string infoActualizacion);
    ~EscenarioVista();
    void cargarFondo();
    void cargarAvion(AvionVista* avionVista, SDL_Renderer* renderer, int numeroJugador);
    void cargarElemento(ElementoVista *elemento, SDL_Renderer *renderer);
    void preloop();
    int mainLoop();
    void agregarAvionVista(string infoAvion);
    void agregarElementoVista(string codigo);
    void agregarDisparoVista(string pathSprite);
    void renderizarAviones();
    void renderizarElementos();
    void renderizarFondo(float y);
    void renderizarDisparos();
    void pushEvento(SDL_Event evento);
    int popEvento();
    void cargarVistasAviones();
    void cargarVistasElementos();
    void cargarVistaDisparos();
    void actualizar(float offset);
    void cerrar();
    void manejarEvento(int evento);
    /* Etapas */
    int comenzarEtapa();
    void avanzarEtapa();
    EtapaVista* etapaActual();
    bool quedanEtapas();
    /* getters y setters*/
    float getScrollingOffset();
    void setScrollingOffset(float scrollingOffset);
    void activar();
    void desactivar();
    list<AvionVista *> &getAviones();
    list<ElementoVista *> &getElementos();
    bool getActivo();
    void setDisparos(list<disparo> disparos);
    int getAncho();
    int getAlto();
    Figura *getFondo();
    Ventana *getVentana();
};

#endif //INC_1942OLDENAIT_ESCENARIOVISTA_HPP
