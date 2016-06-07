#include "escenarioJuego.hpp"

EscenarioJuego::EscenarioJuego(float velocidadDesplazamientoY, int ancho, int alto, int anchoVentana, int altoVentana, string idSprite, int modo) {
    this->velocidadDesplazamientoY = velocidadDesplazamientoY;
    scrollingOffset = 0;
    posicionY = 0;
    this->idSprite = idSprite;
    // Ancho y alto del fondo.
    this->ancho = ancho;
    this->alto = alto;
    this->anchoVentana = anchoVentana;
    this->altoVentana = altoVentana;
    this->grilla = new Grilla(10, 10);


    // Inicio el vector de equipos.
    set<int> equipo1;
    equipos.push_back(equipo1);
    if (modo == COLABORATIVO){
        modoPorEquipos = false;
    } else if (modo == EQUIPOS) {
        modoPorEquipos = true;
        set<int> equipo2;
        equipos.push_back(equipo2);
    } else {
        // TODO excepcion
    }

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

    for (list<PowerUp *>::iterator itPowerUps = powerUps.begin(); itPowerUps != powerUps.end(); itPowerUps++) {
        (*itPowerUps)->volverEstadoInicial();
    }
}

// Se destruyen todas las listas.
EscenarioJuego::~EscenarioJuego() {
    while(!this->aviones.empty()) delete this->aviones.front(), this->aviones.pop_front();
    while(!this->elementos.empty()) delete this->elementos.front(), this->elementos.pop_front();
    while(!this->disparos.empty()) delete this->disparos.front(), this->disparos.pop_front();
    while(!this->powerUps.empty()) delete this->powerUps.front(), this->powerUps.pop_front();
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
    // NOTE provisorio, dado que no hay política de a qué equipo agregarlo.
    equipos[(aviones.size()-1)%equipos.size()].insert(aviones.size());
}

void EscenarioJuego::agregarEnemigo(AvionEnemigo *enemigo) {
    pthread_mutex_lock(&this->mutexListaEnemigos);
    this->enemigos.push_back(enemigo);
    pthread_mutex_unlock(&this->mutexListaEnemigos);
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
            if (disparo != NULL) {
                disparo->setAvion(nroAvion);
                pthread_mutex_lock(&this->mutexListaDisparos);
                disparos.push_back(disparo);
                pthread_mutex_unlock(&this->mutexListaDisparos);
            }
            break;
            // TODO x para la partida para todos?
        default:
            avion(nroAvion)->manejarEvento(evento);
            break;
    }
}

void EscenarioJuego::avanzarEtapa() {
    /* Se desactiva para dar lugar al servidor a hacer otras cosas antes de pasar
    ** de nivel */
    cout << "Se avanza una etapa" << endl;
    desactivar();
    ++itEtapa;
}

void EscenarioJuego::comenzarEtapa() {
    this->activar();
    scrollingOffset = 0;
    posicionY = 0;
    disparos.clear();
    elementos = etapaActual()->getElementos();
    powerUps = etapaActual()->getPowerUps();
    cout << "Se agrego a la etapa actual una lista de tamaño " << powerUps.size() << endl;

    /* Se fijan las posiciones de los aviones */
    float d = ancho/(aviones.size() + 1);
    list<Avion*>::iterator it;
    int i = 1;

    for (it = aviones.begin(); it != aviones.end(); ++it) {
        (*it)->setPosicion(d*i - ANCHO_AVION_COMUN/2, 200);
        ++i;
    }

    mainLoop();
    // TODO 2: podría cambiar la imagen de fondo entre etapas? Mejor no preguntar :P
}

void EscenarioJuego::getProximoEnemigo() {
    Etapa* etapa = this->etapaActual();
    AvionEnemigo* nuevoEnemigo = etapa->getSiguienteEnemigo(this->posicionY);
    if (nuevoEnemigo != NULL){
        this->agregarEnemigo(nuevoEnemigo);
    }
}

void EscenarioJuego::actualizarScrollingOffset(float timeStep) {
    pthread_mutex_lock(&this->mutexScroll);
    scrollingOffset = scrollingOffset + timeStep * velocidadDesplazamientoY;
    if(posicionY >= getLongitud()){
        // Se termina una etapa y se pasa a la siguiente.
        this->avanzarEtapa();
    }
    if (scrollingOffset > alto){
        scrollingOffset = 0;
    }
    pthread_mutex_unlock(&this->mutexScroll);
}

void EscenarioJuego::mainLoop() {
    activar();
//    Trayectoria* cuadrada = new TrayectoriaCuadrada();
//    AvionEnemigo* enemigo = new AvionPequenio((float)50,(float)50,(float)200,(float)0,(float)100, cuadrada);
//    Trayectoria* trayectoriaAvionGrande = new TrayectoriaAvionGrande();
//    AvionEnemigo* enemigoGrande = new AvionGrande((float)500,(float)799,(float)100,(float)0,(float)100, trayectoriaAvionGrande);
//    escenario->agregarEnemigo(enemigo);
//    escenario->agregarEnemigo(enemigoGrande);
    while (estaActivo()) {
        float timeStep = temporizador.getTicks() / 1000.f;
        temporizador.comenzar();
        actualizarEstado(timeStep);
        usleep(5000);
    }
}

void EscenarioJuego::actualizarEstado(float timeStep) {
    this->actualizarScrollingOffset(timeStep);
    this->posicionY = this->posicionY + timeStep * this->velocidadDesplazamientoY;
    this->moverAviones(timeStep);
    this->moverElementos(timeStep);
    this->moverDisparos(timeStep);
    this->moverEnemigos(timeStep);
    this->moverPowerUps(timeStep); //hijo de puta que trae problemas
    this->verificarColisiones();
    this->manejarProximoEvento();
    this->getProximoEnemigo();
}

void EscenarioJuego::jugar(bool serverActivo) {
    itEtapa = etapas.begin();
    comenzarEtapa();
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
                // Por ahora se añade el puntaje cuando el disparo se va de la pantalla.
                subirPuntaje(1, (*iterador)->getNroAvion());
                // Se borra el disparo.
                delete (*iterador);
                pthread_mutex_lock(&this->mutexListaDisparos);
                iterador = disparos.erase(iterador);
                pthread_mutex_unlock(&this->mutexListaDisparos);
            }
        }
    }
}

void EscenarioJuego::moverPowerUps(float timeStep) {
    for (list<PowerUp *>::iterator iterador = this->getPowerUps().begin();
         iterador != this->getPowerUps().end(); ++iterador) {
        PowerUp *powerUp = *iterador;
        //powerUp->mover(timeStep, this->velocidadDesplazamientoY);
    }   
}

void EscenarioJuego::subirPuntaje(int puntos, int nroAvion) {
    avion(nroAvion)->sumarPuntos(puntos);
}

void EscenarioJuego::moverEnemigos(float timeStep) {
    if (this->enemigos.size() > 0) {
        for (list<AvionEnemigo *>::iterator iterador = enemigos.begin(); iterador != enemigos.end(); iterador++) {
            if ((*iterador)->mover(timeStep) == 0) {
                delete (*iterador);
                pthread_mutex_lock(&this->mutexListaEnemigos);
                iterador = enemigos.erase(iterador);
                pthread_mutex_unlock(&this->mutexListaEnemigos);
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

list<PowerUp *> &EscenarioJuego::getPowerUps(){
    return this->powerUps;
}

list<Disparo *> EscenarioJuego::getDisparos() {
    list<Disparo *> listaDisparos;
    pthread_mutex_lock(&this->mutexListaDisparos);
        listaDisparos = this->disparos;
    pthread_mutex_unlock(&this->mutexListaDisparos);
    return listaDisparos;
}

list <AvionEnemigo *> EscenarioJuego::getEnemigos() {
    list<AvionEnemigo *> listaEnemigos;
    pthread_mutex_lock(&this->mutexListaEnemigos);
    listaEnemigos = this->enemigos;
    pthread_mutex_unlock(&this->mutexListaEnemigos);
    return listaEnemigos;
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

int EscenarioJuego::getPuntaje(int nroEquipo) {
    int puntaje = 0;
    set<int>::iterator it;
    for (it = equipos[nroEquipo].begin(); it != equipos[nroEquipo].end(); ++it) {
        puntaje += avion((*it))->getPuntaje();
    }
    return puntaje;
}

bool EscenarioJuego::quedanEtapas() {
    return itEtapa != etapas.end();
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

bool EscenarioJuego::porEquipos() {
    return modoPorEquipos;
}

void EscenarioJuego::verificarColisiones(){
    this->grilla->ubicarAviones(this->aviones);
    this->grilla->ubicarDisparosAmigos(this->disparos);
    this->grilla->ubicarEnemigos(this->enemigos);
    this->grilla->verificarColisiones();
    this->grilla->limpiarGrilla();
}
