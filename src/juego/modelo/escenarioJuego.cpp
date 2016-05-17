#include "escenarioJuego.hpp"

EscenarioJuego::EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, int longitud, string idSprite) {
    this->velocidadDesplazamientoY = velocidadDesplazamientoY;
    scrollingOffset = 0;
    posicionY = 0;
    this->idSprite = idSprite;
    // Ancho y alto de la ventana.
    this->ancho = ancho;
    this->alto = alto;
    // Longitud del nivel.
    this->longitud = longitud;
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

//Se destruyen todas las listas.
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

void EscenarioJuego::agregarAvion(float posX, float posY, float velocidad, float velocidadDisparos, string idSprite,
                                  string idSpriteDisparos) {
    Avion *avion = new Avion(posX, posY, velocidad, velocidadDisparos, idSprite, idSpriteDisparos);
    this->aviones.push_back(avion);
}

void EscenarioJuego::agregarElemento(float posX, float posY, string idSprite) {
    Elemento *elemento = new Elemento(posX, posY, idSprite);
    this->elementos.push_back(elemento);
}

void EscenarioJuego::manejarEvento(int nroAvion, int evento) {
    Disparo * disparo;
    switch (evento) {
        case PRESIONA_R:
            reset();
            break;
        case PRESIONA_ESPACIO:
            disparo = avion(nroAvion)->disparar();
            if (disparo) disparos.push_back(disparo);
            break;
        default:
            avion(nroAvion)->manejarEvento(evento);
            break;
    }
}

void EscenarioJuego::actualizarScrollingOffset(float timeStep) {
    pthread_mutex_lock(&this->mutexScroll);
    scrollingOffset = scrollingOffset + timeStep * velocidadDesplazamientoY;
    if(posicionY >= longitud){
        this->reset();
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
        escenario->actualizarScrollingOffset(timeStep);
        escenario->posicionY = escenario->posicionY + timeStep * escenario->velocidadDesplazamientoY;
        escenario->temporizador.comenzar();
        escenario->moverAviones(timeStep);
        escenario->moverElementos(timeStep);
        escenario->moverDisparos(timeStep);
        escenario->manejarProximoEvento();
        usleep(5000);
    }

    pthread_exit(NULL);
}

void EscenarioJuego::mainLoop(bool serverActivo) {
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
                iterador = disparos.erase(iterador);
            }
        }
    }
}

/* getters */
list<Avion *> &EscenarioJuego::getAviones() {
    return this->aviones;
}


list<Elemento *> &EscenarioJuego::getElementos() {
    return this->elementos;
}

list<Disparo *> &EscenarioJuego::getDisparos() {
    return this->disparos;
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
    return this->longitud;
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
