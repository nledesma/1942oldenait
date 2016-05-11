#include "escenarioJuego.hpp"

EscenarioJuego::EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, string idSprite) {
    this->velocidadDesplazamientoY = velocidadDesplazamientoY;
    scrollingOffset = 0;
    posicionY = 0;
    this->idSprite = idSprite;
    this->ancho = ancho;
    this->alto = alto;
}

void EscenarioJuego::reset() {
    disparos.clear();
    for (list<Avion *>::iterator itAviones = aviones.begin(); itAviones != aviones.end(); itAviones++) {
        (*itAviones)->volverEstadoInicial();
    }
    for (list<Elemento *>::iterator itElementos = elementos.begin(); itElementos != elementos.end(); itElementos++) {
        (*itElementos)->volverEstadoInicial();
    }
}

EscenarioJuego::~EscenarioJuego() { }

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
    list<Avion *>::iterator iterador;
    switch (evento) {
        case PRESIONA_R:
            reset();
            break;
        case PRESIONA_ESPACIO:
            iterador = aviones.begin();
            advance(iterador, nroAvion - 1);
            disparos.push_back((*iterador)->disparar());
            // TODO Hay que hacerle delete a esto en algún momento.
            break;
        case PRESIONA_ENTER:
            iterador = aviones.begin();
            advance(iterador, nroAvion - 1);
            //TODO debe haber una manera mas elegante de hacerlo! Y no anda encima
            (*iterador)->setEstadoAnimacion((int)LOOP_ETAPA_1);
        default:
            // NOTE ojo, tienen que estar en orden los aviones.
            iterador = aviones.begin();
            advance(iterador, nroAvion - 1);
            (*iterador)->manejarEvento(evento);
            break;
    }
}

void EscenarioJuego::actualizarScrollingOffset(float timeStep) {
    pthread_mutex_lock(&this->mutexScroll);
    scrollingOffset = scrollingOffset + timeStep * velocidadDesplazamientoY;
    if (scrollingOffset > alto){
        scrollingOffset = 0;
    }
    pthread_mutex_unlock(&this->mutexScroll);
}

void *EscenarioJuego::mainLoop_th(void *THIS) {
    EscenarioJuego *escenario = (EscenarioJuego *) THIS;
    bool quit = false;
    while (!quit) {
        float timeStep = escenario->temporizador.getTicks() / 1000.f;
        escenario->actualizarScrollingOffset(timeStep);
        escenario->posicionY = escenario->posicionY + timeStep * escenario->velocidadDesplazamientoY;
        // TODO Por qué se comienza acá de todos los lugares? Fucking lazyfoo.
        escenario->temporizador.comenzar();
        escenario->moverAviones(timeStep);
        escenario->moverElementos(timeStep);
        escenario->moverDisparos(timeStep);
        escenario->manejarProximoEvento();
    }

    pthread_exit(NULL);
}

void EscenarioJuego::mainLoop() {
    pthread_create(&mainLoopThread, NULL, mainLoop_th, (void *) this);
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
        //avion->moverDisparos(timeStep);
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
