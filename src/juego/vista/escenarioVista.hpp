#ifndef INC_1942OLDENAIT_ESCENARIOVISTA_HPP
#define INC_1942OLDENAIT_ESCENARIOVISTA_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include "ventana.hpp"
#include "avionVista.hpp"
#include "figura.hpp"
#include "elementoVista.hpp"
#include "etapaVista.hpp"
#include "disparoVista.hpp"
#include "soundboard.hpp"
#include "../../accesorios/colaConcurrente/colaConcurrente.hpp"
#include "../../accesorios/temporizador.hpp"
#include <list>
#include <iterator>
#include <pthread.h>
#include "../../accesorios/default.hpp"
#include "enemigoPequenio.hpp"
#include "enemigoDeEscuadron.hpp"
#include "enemigoMediano.hpp"
#include "enemigoGrande.hpp"
#include "powerUpBonificacionVista.hpp"
#include "powerUpDosAmetralladorasVista.hpp"
#include "powerUpDestruirEnemigosVista.hpp"
#include "powerUpAvionesSecundariosVista.hpp"
#include "powerUpBonificacion1500Vista.hpp"
#include "disparoEnemigoVista.hpp"
#include "textoDinamico.hpp"
#include <sstream>

#define POSX_PUNTAJE1 10
#define POSX_PUNTAJE2 600
#define POSY_PUNTAJES 10

using namespace std;

struct enemigo {
    float posX;
    float posY;
    int estadoAnimacion;
    int tipoEnemigo;
};

struct powerUp{
  float posX;
  float posY;
  int estadoAnimacion;
  int tipoPowerUp;
  int valorPowerUp;
};

class EscenarioVista {
private:
    /* Equipos */
    bool porEquipos;
    vector<int> puntajes;
    vector<TextoDinamico *> textosPuntaje;
    vector<Texto*> titulosPuntaje;
    /* Número de avión que le corresponde a este cliente */
    int nroAvion;
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
    DisparoEnemigoVista* disparoEnemigoVista;
    EnemigoPequenio* enemigoPequenio;
    EnemigoDeEscuadron* enemigoDeEscuadron;
    EnemigoMediano* enemigoMediano;
    EnemigoGrande* enemigoGrande;
    list<powerUp> powerUps;
    list<disparo> disparos;
    list<disparoEnemigo> disparosEnemigos;
    list<enemigo> enemigos;
    PowerUpAvionesSecundariosVista* powerUpAvionesSecundarios;
    PowerUpBonificacionVista* powerUpBonificacion;
    PowerUpDestruirEnemigosVista* powerUpDestruirEnemigos;
    PowerUpDosAmetralladorasVista* powerUpDosAmetralladoras;
    PowerUpBonificacion1500Vista* powerUpBonificacion1500;
    /* Etapas */
    list<EtapaVista*> etapas;
    SoundBoard *soundBoard;
    int contadorSonido;
    list<EtapaVista*>::iterator itEtapa;
    /* Estado */
    bool activo = false;
    /* Sincronización */
    pthread_mutex_t mutexActualizar = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexDisparos = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexDisparosEnemigos = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexEnemigos = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexPowerUps = PTHREAD_MUTEX_INITIALIZER;
    ColaConcurrente <int> colaEventos;
    void actualizarImagenPuntajes();
    Figura* figuraVidas;
    Texto* textoIniciarPartida;
    Texto* textoPerdedor;
    bool finalizado = false;
public:
    /* Constructor y destructor */
    EscenarioVista(string infoEscenario, Ventana* ventana);
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
    void agregarDisparoEnemigoVista();
    void agregarVistasEnemigos();
    void agregarVistasPowerUps();
    void renderizarAviones();
    void renderizarElementos();
    void renderizarFondo(float y);
    void renderizarDisparos();
    void renderizarDisparosEnemigos();
    void renderizarEnemigos();
    void renderizarPowerUps();
    void renderizarPuntajes();
    void pushEvento(SDL_Event evento);
    int popEvento();
    void cargarVistasAviones();
    void cargarVistasElementos();
    void cargarVistaDisparos();
    void cargarVistaDisparosEnemigos();
    void cargarVistaEnemigos();
    void cargarVistasPowerUps();
    void cargarSonidos();
    void cargarVistaVidas();
    void actualizar(float offset);
    void cerrar();
    void manejarEvento(int evento);
    /* Etapas */
    int comenzarEtapa();
    void avanzarEtapa();
    EtapaVista* etapaActual();
    bool quedanEtapas();
    void finalizarJuego();
    /* getters y setters*/
    float getScrollingOffset();
    void setScrollingOffset(float scrollingOffset);
    void activar();
    void desactivar();
    list<AvionVista *> &getAviones();
    list<ElementoVista *> &getElementos();
    bool getActivo();
    void setDisparos(list<disparo> disparos);
    void setDisparosEnemigos(list<disparoEnemigo> disparosEnemigos);
    void setEnemigos(list<enemigo> enemigosParam);
    void setPowerUps(list<powerUp> powerUpsParam);
    int getAncho();
    int getAlto();
    Figura *getFondo();
    Ventana *getVentana();
    void renderizarImagenVidas();
    void renderizarTextoIniciarPartida();
};

#endif //INC_1942OLDENAIT_ESCENARIOVISTA_HPP
