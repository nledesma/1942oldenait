#include "escenarioJuego.hpp"

EscenarioJuego::EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, int anchoVentana, int altoVentana, string idSprite) {
    this->velocidadDesplazamientoY = velocidadDesplazamientoY;
    scrollingOffset = 0;
    posicionY = 0;
    this->idSprite = idSprite;
    // Ancho y alto del fondo.
    this->ancho = ancho;
    this->alto = alto;
    this->anchoVentana = anchoVentana;
    this->altoVentana = altoVentana;
}

void EscenarioJuego::reset() {
    disparos.clear();
    posicionY = 0;
    for (list<Avion *>::iterator itAviones = aviones.begin(); itAviones != aviones.end(); itAviones++) {
        (*itAviones)->volverEstadoInicial();
    }
    for (list<Elemento *>::iterator itElementos = elementos.begin(); itElementos != elementos.end(); itElementos++) {
        (*itElementos)->volverEstadoInicial();
    }
}

// Se destruyen todas las listas.
EscenarioJuego::~EscenarioJuego() {
    while(!this->aviones.empty()) delete this->aviones.front(), this->aviones.pop_front();
    while(!this->elementos.empty()) delete this->elementos.front(), this->elementos.pop_front();
    while(!this->disparos.empty()) delete this->disparos.front(), this->disparos.pop_front();
}

float EscenarioJuego::getScrollingOffset() {
    pthread_mutex_lock(&this->mutexScroll);
    float offset = this->scrollingOffset;
    pthread_mutex_unlock(&this->mutexScroll);
    return offset;
}

void EscenarioJuego::agregarAvion(float velocidad, float velocidadDisparos, string idSprite,
                                  string idSpriteDisparos) {
    float posX = 0, posY = 0; // Habría que hacer un constructor sin posiciones.
    Avion *avion = new Avion(posX, posY, velocidad, velocidadDisparos, idSprite, idSpriteDisparos);
    this->aviones.push_back(avion);
}

void EscenarioJuego::agregarEtapa(Etapa * etapa) {
    this->etapas.push_back(etapa);
}

void EscenarioJuego::manejarEvento(int nroAvion, int evento) {
    Disparo * disparo;
    switch (evento) {
        case PRESIONA_R:
            reset();
            break;
        case PRESIONA_ESPACIO:
            disparo = avion(nroAvion)->disparar();
            if (disparo){
                pthread_mutex_lock(&this->mutexListaDisparos);
                disparos.push_back(disparo);
                pthread_mutex_unlock(&this->mutexListaDisparos);
            }
            break;
        default:
            avion(nroAvion)->manejarEvento(evento);
            break;
    }
}

void EscenarioJuego::siguienteEtapa() {
    ++itEtapa;
    if (itEtapa == etapas.end()) {
        desactivar();
    } else {
        comenzarEtapa();
    }
}

void EscenarioJuego::comenzarEtapa() {
    scrollingOffset = 0;
    posicionY = 0;
    disparos.clear();
    elementos = etapaActual()->getElementos();

    /* Se fijan las posiciones de los aviones */
    float d = ancho/(aviones.size() + 1);
    list<Avion*>::iterator it;
    int i = 1;

    for (it = aviones.begin(); it != aviones.end(); ++it) {
        (*it)->setPosicion(d*i - ANCHO_AVION_COMUN/2, 200);
        ++i;
    }

    // TODO 2: podría cambiar la imagen de fondo entre etapas? Mejor no preguntar :P
}

void EscenarioJuego::actualizarScrollingOffset(float timeStep) {
    pthread_mutex_lock(&this->mutexScroll);
    scrollingOffset = scrollingOffset + timeStep * velocidadDesplazamientoY;
    if(posicionY >= getLongitud()){
        // Se termina una etapa y se pasa a la siguiente.
        this->siguienteEtapa();
    }
    if (scrollingOffset > alto){
        scrollingOffset = 0;
    }
    pthread_mutex_unlock(&this->mutexScroll);
}

void *EscenarioJuego::mainLoop_th(void *THIS) {
    EscenarioJuego *escenario = (EscenarioJuego *) THIS;
    escenario->activar();
    while (escenario->estaActivo()) {
        float timeStep = escenario->temporizador.getTicks() / 1000.f;
        escenario->temporizador.comenzar();
        escenario->actualizarEstado(timeStep);
        usleep(5000);
    }
    pthread_exit(NULL);
}

void EscenarioJuego::actualizarEstado(float timeStep) {
    this->actualizarScrollingOffset(timeStep);
    this->posicionY = this->posicionY + timeStep * this->velocidadDesplazamientoY;
    this->moverAviones(timeStep);
    this->moverElementos(timeStep);
    this->moverDisparos(timeStep);
    this->manejarProximoEvento();
}

void EscenarioJuego::jugar(bool serverActivo) {
    itEtapa = etapas.begin();
    comenzarEtapa();
    if (serverActivo){
        pthread_create(&mainLoopThread, NULL, mainLoop_th, (void *) this);
    }
}

void EscenarioJuego::manejarProximoEvento() {
    if (!this->colaEventos.vacia()) {
        pair<int, int> evento = this->colaEventos.pop();
        this->manejarEvento(evento.first, evento.second);
    }
}

void EscenarioJuego::pushEvento(pair<int, int> evento) {
    this->colaEventos.push(evento);
}

void EscenarioJuego::moverAviones(float timeStep) {
    for (list<Avion *>::iterator iterador = this->getAviones().begin();
         iterador != this->getAviones().end(); ++iterador) {
        Avion *avion = *iterador;
        avion->mover(timeStep);
    }
}

void EscenarioJuego::moverElementos(float timeStep) {
    for (list<Elemento *>::iterator iterador = this->getElementos().begin();
         iterador != this->getElementos().end(); ++iterador) {
        Elemento *elemento = *iterador;
        elemento->mover(timeStep, this->velocidadDesplazamientoY);
    }
}

void EscenarioJuego::moverDisparos(float timeStep) {
    if (this->disparos.size() > 0) {
        for (list<Disparo *>::iterator iterador = disparos.begin(); iterador != disparos.end(); iterador++) {
            if ((*iterador)->mover(timeStep) == 0) {
                delete (*iterador);
                pthread_mutex_lock(&this->mutexListaDisparos);
                iterador = disparos.erase(iterador);
                pthread_mutex_unlock(&this->mutexListaDisparos);
            }
        }
    }
}

/* getters & setters */
list<Avion *> &EscenarioJuego::getAviones() {
    return this->aviones;
}


list<Elemento *> &EscenarioJuego::getElementos() {
    return this->elementos;
}

list<Disparo *> EscenarioJuego::getDisparos() {
    list<Disparo *> listaDisparos;
    pthread_mutex_lock(&this->mutexListaDisparos);
        listaDisparos = this->disparos;
    pthread_mutex_unlock(&this->mutexListaDisparos);
    return listaDisparos;
}

string EscenarioJuego::getIdSprite() {
    return this->idSprite;
}

int EscenarioJuego::getAncho() {
    return this->ancho;
}

int EscenarioJuego::getAlto() {
    return this->alto;
}

int EscenarioJuego::getLongitud() {
    return this->etapaActual()->getLongitud();
}

Etapa * EscenarioJuego::etapaActual() {
    return *itEtapa;
}

list<Etapa *> EscenarioJuego::getEtapas() {
    // copia de lista de etapas.
    return etapas;
}

bool EscenarioJuego::estaActivo() {
    return this->motorActivado;
}

void EscenarioJuego::desactivar() {
    this->motorActivado = false;
    colaEventos.avisar();
}

void EscenarioJuego::activar() {
    this->motorActivado = true;
}

Avion* EscenarioJuego::avion(int i){
    list<Avion*>::iterator it = aviones.begin();
    advance (it, i - 1);
    return *it;
}

int EscenarioJuego::getAnchoVentana() {
    return anchoVentana;
}

int EscenarioJuego::getAltoVentana() {
    return altoVentana;
}
