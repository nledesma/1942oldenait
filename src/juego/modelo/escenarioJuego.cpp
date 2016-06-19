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
    this->grilla = new Grilla(12, 12);
    this->nroEtapaActual = 0; // La 0 es la primera.
    this->modoPractica = false;

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
    this->enemigos.clear();
    this->disparosEnemigos.clear();
    for (list<Avion *>::iterator itAviones = aviones.begin(); itAviones != aviones.end(); itAviones++) {
        (*itAviones)->setPosicionInicial();
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
                                  string idSpriteDisparos, int numeroAvion, int vidas) {
    float posX = 0, posY = 0; // Habría que hacer un constructor sin posiciones.
    float posXFinal;
    float posYFinal;
    switch ((int)aviones.size()){
        case 0:
            posXFinal = 250;
            posYFinal = 190;
            break;
        case 1:
            posXFinal = 450;
            posYFinal = 190;
            break;
        case 2:
            posXFinal = 250;
            posYFinal = 350;
            break;
        case 3:
            posXFinal = 450;
            posYFinal = 350;
            break;
        case 4:
            posXFinal = 210;
            posYFinal = 300;
            break;
        case 5:
            posXFinal = 490;
            posYFinal = 300;
            break;
    }
    Avion *avion = new Avion(posX, posY, velocidad, velocidadDisparos, idSprite, idSpriteDisparos, numeroAvion, vidas, posXFinal, posYFinal);
    this->aviones.push_back(avion);
}

void EscenarioJuego::setEquipo(int nroAvion, int equipo) {
    if (equipo != 0 && equipo != 1) {
        cout << "Error en el equipo recibido ("<< equipo <<"), se le asigna el equipo 1." << endl;
        equipo = 0;
    }
    equipos[equipo].insert(nroAvion);
}

void EscenarioJuego::agregarEnemigo(AvionEnemigo *enemigo) {
    pthread_mutex_lock(&this->mutexListaEnemigos);
    this->enemigos.push_back(enemigo);
    pthread_mutex_unlock(&this->mutexListaEnemigos);
}

void EscenarioJuego::agregarEtapa(Etapa * etapa) {
    this->etapas.push_back(etapa);
}

bool EscenarioJuego::manejarEvento(int nroAvion, int evento) {
    vector<Disparo *> disparo;
    bool resetea = false;
    switch (evento) {
        case PRESIONA_R:
            resetea = true;
            break;
        case PRESIONA_ESPACIO:
            disparo = avion(nroAvion)->disparar();
            if (!disparo.empty()) {
                for (unsigned int i = 0; i < disparo.size(); i++) {
                    disparo[i]->setAvion(nroAvion);
                    pthread_mutex_lock(&this->mutexListaDisparos);
                    disparos.push_back(disparo[i]);
                    pthread_mutex_unlock(&this->mutexListaDisparos);
                }
            }
            break;
        case PRESIONA_L:
            this->modoPractica = !this->modoPractica;
            break;
            // TODO x para la partida para todos?
        default:
            avion(nroAvion)->manejarEvento(evento);
            break;
    }
    return resetea;
}

void EscenarioJuego::avanzarEtapa() {
    /* Se desactiva para dar lugar al servidor a hacer otras cosas antes de pasar
    ** de nivel */
    ++nroEtapaActual;
    cout << "Se avanza a la etapa " << nroEtapaActual + 1 << "." << endl;
    desactivar();
    ++itEtapa;
}

void EscenarioJuego::reiniciarEtapas() {
    desactivar();
    nroEtapaActual = 0;
    usleep(5000);
    this->itEtapa = etapas.begin();
    pthread_mutex_lock(&mutexPowerUps);
    this->powerUps.clear();
    pthread_mutex_unlock(&mutexPowerUps);
    pthread_mutex_lock(&mutexListaEnemigos);
    this->enemigos.clear();
    pthread_mutex_unlock(&mutexListaEnemigos);
    pthread_mutex_lock(&mutexListaDisparosEnemigos);this->disparos.clear();
    this->disparosEnemigos.clear();
    pthread_mutex_unlock(&mutexListaDisparosEnemigos);
    pthread_mutex_lock(&mutexListaDisparos);this->disparos.clear();
    this->disparos.clear();
    pthread_mutex_unlock(&mutexListaDisparos);

    for (list<Etapa *>::iterator itEtapas = etapas.begin(); itEtapas != etapas.end(); itEtapas++) {
        (*itEtapas)->setEstadosIniciales();
    }

    for (list<Avion *>::iterator itAviones = aviones.begin(); itAviones != aviones.end(); itAviones++) {
        (*itAviones)->volverEstadoInicial();
    }
    cout << " size powerUps: " << powerUps.size() << " size enemigos: " << enemigos.size() << " size disparos: " << disparos.size() << " size disparosEnemigos: " << disparosEnemigos.size() << " size elementos: " << elementos.size() << endl;
    while (!this->colaEventos.vacia()) {
        this->colaEventos.pop();
    }
    temporizador.detener();

}

int EscenarioJuego::comenzarEtapa() {
    this->activar();
    scrollingOffset = 0;
    posicionY = 0;
    disparos.clear();
    this->infoEscuadrones.clear();
    elementos = etapaActual()->getElementos();
    powerUps = etapaActual()->getPowerUps();
    etapaActual()->resetEnemigos();
    cout << " size powerUps: " << powerUps.size() << " size enemigos: " << enemigos.size() << " size disparos: " << disparos.size() << " size disparosEnemigos: " << disparosEnemigos.size() << " size elementos: " << elementos.size() << endl;

    return mainLoop();
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
    if (scrollingOffset > alto){
        scrollingOffset = 0;
    }
    pthread_mutex_unlock(&this->mutexScroll);
}

int EscenarioJuego::mainLoop() {
    activar();
    int eventoFinal = AVANZAR_ETAPA;
//    Trayectoria* cuadrada = new TrayectoriaCuadrada();
//    AvionEnemigo* enemigo = new AvionPequenio((float)50,(float)50,(float)200,(float)0,(float)100, cuadrada);
//    Trayectoria* trayectoriaAvionGrande = new TrayectoriaAvionGrande();
//    AvionEnemigo* enemigoGrande = new AvionGrande((float)500,(float)799,(float)100,(float)0,(float)100, trayectoriaAvionGrande);
//    escenario->agregarEnemigo(enemigo);
//    escenario->agregarEnemigo(enemigoGrande);
    while (estaActivo()) {
        float timeStep = temporizador.getTicks() / 1000.f;
        temporizador.comenzar();
        eventoFinal = actualizarEstado(timeStep);
        usleep(5000);
    }
    return eventoFinal;
}

int EscenarioJuego::actualizarEstado(float timeStep) {
    bool resetear = false;
    int eventoFinal = AVANZAR_ETAPA;
    if (this->posicionY < this->etapaActual()->getLongitud() - 800) {
        this->actualizarScrollingOffset(timeStep);
        if(!this->modoPractica){
            this->sortearDisparosEnemigos(timeStep);
        }
        this->posicionY = this->posicionY + timeStep * this->velocidadDesplazamientoY;
        this->moverAviones(timeStep);
        this->moverElementos(timeStep);
        this->moverEnemigos(timeStep);
        this->moverPowerUps(timeStep);
        this->proyectarDisparos(timeStep);
        this->moverDisparosEnemigos(timeStep);
        resetear = this->manejarProximoEvento();
        this->verificarColisiones();
        this->moverDisparos(timeStep);
        this->getProximoEnemigo();
    } else {
        this->moverEnemigos(timeStep);
        this->moverDisparosEnemigos(timeStep);
        this->moverDisparos(timeStep);
        bool avionesEstacionados = this->moverAvionesAposicionFinal(timeStep);
        if (avionesEstacionados){
            pthread_mutex_lock(&this->mutexListaEnemigos);
            this->enemigos.clear();
            pthread_mutex_unlock(&this->mutexListaEnemigos);
            pthread_mutex_lock(&this->mutexPowerUps);
            this->powerUps.clear();
            pthread_mutex_unlock(&this->mutexPowerUps);
            pthread_mutex_lock(&this->mutexListaDisparos);
            this->disparos.clear();
            pthread_mutex_unlock(&this->mutexListaDisparos);
            pthread_mutex_lock(&this->mutexListaDisparosEnemigos);
            this->disparosEnemigos.clear();
            pthread_mutex_unlock(&this->mutexListaDisparosEnemigos);
            while (!this->colaEventos.vacia()) {
                this->colaEventos.pop();
            }
            temporizador.detener();
            this->avanzarEtapa();
            for (list<Avion *>::iterator itAviones = this->aviones.begin(); itAviones != this->aviones.end(); itAviones++) {
                (*itAviones)->setPosicionInicial(false);
            }
        }
    }
    if (resetear){
        this->reiniciarEtapas();
        eventoFinal = REINICIAR_ESCENARIO;
    }
    return eventoFinal;
}

void EscenarioJuego::sortearDisparosEnemigos(float timeStep) {
    int randomDisparo = rand() % 400;
    int cantidadEnemigos = (int) this->getEnemigos().size();
    if (randomDisparo == 0 && cantidadEnemigos != 0){
        int randomEnemigo = rand() % cantidadEnemigos;

        AvionEnemigo* enemigo = this->avionEnemigo(randomEnemigo);

        if (enemigo->getTipoAvion() != TIPO_AVION_GRANDE){
            int cantidadAviones = (int) this->getAviones().size();
            int randomAliado = rand() % cantidadAviones;
            Avion* aliado = this->avion(randomAliado + 1);
            float xObjetivo = aliado->getPosicionX();
            float yObjetivo = aliado->getPosicionY();

            pthread_mutex_lock(&mutexListaEnemigos);
            DisparoEnemigo* disparoEnemigo = enemigo->disparar(xObjetivo, yObjetivo);
            pthread_mutex_unlock(&mutexListaEnemigos);

            if (disparoEnemigo != NULL){
                pthread_mutex_lock(&this->mutexListaDisparosEnemigos);
                this->disparosEnemigos.push_back(disparoEnemigo);
                pthread_mutex_unlock(&this->mutexListaDisparosEnemigos);
            }
        }
    }

    if (this->motorActivado && enemigos.size() > 0) {
        for (list<AvionEnemigo *>::iterator iterador = enemigos.begin();
             iterador != enemigos.end(); ++iterador) {
            AvionEnemigo *avionEnemigo = *iterador;
            if (avionEnemigo->getTipoAvion() == TIPO_AVION_GRANDE) {
                if (avionEnemigo->correspondeDisparar(timeStep)) {
                    vector<DisparoEnemigo*> disparos = avionEnemigo->disparar();
                    for (vector<DisparoEnemigo *>::iterator it = disparos.begin(); it != disparos.end(); ++it) {
                        DisparoEnemigo *disparoEnemigoGrande = *it;
                        pthread_mutex_lock(&this->mutexListaDisparosEnemigos);
                        this->disparosEnemigos.push_back(disparoEnemigoGrande);
                        pthread_mutex_unlock(&this->mutexListaDisparosEnemigos);
                    }
                }
            }
        }
    }
}

int EscenarioJuego::jugar(bool serverActivo) {
    // TODO POS
    /* Se fijan las posiciones de los aviones */
    float d = ancho/(aviones.size() + 1);
    list<Avion*>::iterator it;
    int i = 1;

    for (it = aviones.begin(); it != aviones.end(); ++it) {
        (*it)->setSpawn(d*i - ANCHO_AVION_COMUN/2, 600);
        (*it)->setPosicion(d*i - ANCHO_AVION_COMUN/2, 600);
        ++i;
    }

    itEtapa = etapas.begin();
    return comenzarEtapa();
}

bool EscenarioJuego::manejarProximoEvento() {
    bool resetear = false;
    if (!this->colaEventos.vacia()) {
        pair<int, int> evento = this->colaEventos.pop();
        resetear = this->manejarEvento(evento.first, evento.second);
    }
    return resetear;
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

bool EscenarioJuego::moverAvionesAposicionFinal(float timeStep) {
    bool resultado = true;
    for (list<Avion *>::iterator iterador = this->getAviones().begin();
         iterador != this->getAviones().end(); ++iterador) {
        Avion *avion = *iterador;
        if (!avion->moverAPosicionFinal(timeStep)){
            resultado = false;
        }
    }
    return resultado;
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
//                // Por ahora se añade el puntaje cuando el disparo se va de la pantalla.
//                subirPuntaje(1, (*iterador)->getNroAvion());
//                // Se borra el disparo.
                delete (*iterador);
                pthread_mutex_lock(&this->mutexListaDisparos);
                iterador = disparos.erase(iterador);
                pthread_mutex_unlock(&this->mutexListaDisparos);
            }
        }
    }
}

void EscenarioJuego::moverDisparosEnemigos(float timeStep) {
    if (this->disparosEnemigos.size() > 0) {
        for (list<DisparoEnemigo *>::iterator iterador = disparosEnemigos.begin(); iterador != disparosEnemigos.end(); iterador++) {
            if ((*iterador)->mover(timeStep) == 0) {
                // Se borra el disparo.
                delete (*iterador);
                pthread_mutex_lock(&this->mutexListaDisparosEnemigos);
                iterador = disparosEnemigos.erase(iterador);
                pthread_mutex_unlock(&this->mutexListaDisparosEnemigos);
            }
        }
    }
}

void EscenarioJuego::moverPowerUps(float timeStep) {
    for (list<PowerUp *>::iterator iterador = powerUps.begin();
         iterador != powerUps.end(); iterador++) {
        if((*iterador)->mover(timeStep, this->velocidadDesplazamientoY) == 0){
            pthread_mutex_lock(&this->mutexPowerUps);
            iterador = powerUps.erase(iterador);
            pthread_mutex_unlock(&this->mutexPowerUps);
        }
    }
}

void EscenarioJuego::subirPuntaje(int puntos, int nroAvion) {
    avion(nroAvion)->sumarPuntos(puntos);
}

void EscenarioJuego::moverEnemigos(float timeStep) {
    if (this->enemigos.size() > 0) {
        for (list<AvionEnemigo *>::iterator iterador = enemigos.begin(); iterador != enemigos.end(); iterador++) {
//            cout << "Puntos Enemigo:" << endl;
//            cout << (*iterador)->getPosicionX() << " " << (*iterador)->getPosicionY() << " " << (*iterador)->getAngulo() << endl << endl;
//            cout << "Puntos colisionable:" << endl;
//            cout << (*iterador)->getColisionable()->getSuperficiePrincipal()->getDerAbajo()->getPosX() << " " << (*iterador)->getColisionable()->getSuperficiePrincipal()->getDerAbajo()->getPosY() << endl << endl;
//            for(int i = 0; i < (*iterador)->getColisionable()->getSuperficiesSecundarias().size(); i++){
//                cout << (*iterador)->getColisionable()->getSuperficiesSecundarias()[i]->getDerAbajo()->getPosX() << " " << (*iterador)->getColisionable()->getSuperficiesSecundarias()[i]->getDerAbajo()->getPosY() << endl;
//                cout << (*iterador)->getColisionable()->getSuperficiesSecundarias()[i]->getIzqArriba()->getPosX() << " " << (*iterador)->getColisionable()->getSuperficiesSecundarias()[i]->getIzqArriba()->getPosY() << endl;
//                cout << endl;
//            }
//            cout << endl << endl << endl;
             if ((*iterador)->mover(timeStep) == 0) {
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

list<PowerUp *> EscenarioJuego::getPowerUps(){
    list<PowerUp*> listaPowerUps;
    pthread_mutex_lock(&this->mutexPowerUps);
    listaPowerUps = this->powerUps;
    pthread_mutex_unlock(&this->mutexPowerUps);
    return listaPowerUps;
}

list<Disparo *> EscenarioJuego::getDisparos() {
    list<Disparo*> listaDisparos;
    pthread_mutex_lock(&this->mutexListaDisparos);
    listaDisparos = this->disparos;
    pthread_mutex_unlock(&this->mutexListaDisparos);
    return listaDisparos;
}

list<DisparoEnemigo *> EscenarioJuego::getDisparosEnemigos() {
    list<DisparoEnemigo *> listaDisparosEnemigos;
    pthread_mutex_lock(&this->mutexListaDisparosEnemigos);
    listaDisparosEnemigos = this->disparosEnemigos;
    pthread_mutex_unlock(&this->mutexListaDisparosEnemigos);
    return listaDisparosEnemigos;
}

list <AvionEnemigo *> EscenarioJuego::getEnemigos() {
    list<AvionEnemigo*> listaEnemigos;
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

AvionEnemigo* EscenarioJuego::avionEnemigo(int i){
    list<AvionEnemigo*>::iterator it = enemigos.begin();
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
    /*this->grilla->ubicarAviones(this->aviones);
    this->grilla->ubicarDisparosAmigos(this->disparos);
    this->grilla->ubicarEnemigos(this->enemigos);
    this->grilla->verificarColisiones();
    this->grilla->limpiarGrilla();*/

    for(list<Disparo*>::iterator itDisparos = this->disparos.begin(); itDisparos != this->disparos.end(); itDisparos++){
        AvionEnemigo* enemigoAColisionar = NULL;
        //TODO refactor, esto se usa para ver cual es el avion enemigo más cercano al enemigo, pero el codigo quedó horrible
        float cercano = 0;
        for(list<AvionEnemigo*>::iterator itEnemigos = this->enemigos.begin(); itEnemigos != this->enemigos.end(); itEnemigos++){
            int condicionEstaExplotando;
            if ((*itEnemigos)->getTipoAvion() == TIPO_AVION_GRANDE){
                condicionEstaExplotando = AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1;
            } else {
                condicionEstaExplotando = AVION_ENEMIGO_EXPLOSION_ETAPA_1;
            }
            if((*itEnemigos)->getColisionable()->colisiona((*itDisparos)->getColisionable()) && (*itDisparos)->getEstado() == 0  && (*itEnemigos)->getEstadoAnimacion() < condicionEstaExplotando ) {
                if((*itEnemigos)->getPosicionY() > cercano) {
                    cercano = (*itEnemigos)->getPosicionY();
                    enemigoAColisionar = (*itEnemigos);
                }
            }
        }
        if(enemigoAColisionar != NULL && (!enemigoAColisionar->estaColisionando())){
            if(enemigoAColisionar->getTipoAvion() != TIPO_AVION_ESCUADRON){
                subirPuntaje(enemigoAColisionar->estallar(), (*itDisparos)->getNroAvion());
                (*itDisparos)->colisionar();
                if((enemigoAColisionar->getTipoAvion() == TIPO_AVION_GRANDE) && (enemigoAColisionar->getVidas() <= 0)){
                    crearPowerUpBonus(enemigoAColisionar->getPosicionX(),enemigoAColisionar->getPosicionY(),VALOR_POWERUP_1500);
                }
            } else {
                subirPuntaje(enemigoAColisionar->estallar() + this->validarBonificacionEscuadron(enemigoAColisionar, (*itDisparos)->getNroAvion()), (*itDisparos)->getNroAvion());
                (*itDisparos)->colisionar();
            }
            avion((*itDisparos)->getNroAvion())->aumentarAciertos();
        }
    }

    for(list<Avion*>::iterator itAviones = this->aviones.begin(); itAviones != this->aviones.end(); itAviones++){
        if ((*itAviones)->getContadorTiempoInmunidad() == 0 && (!this->modoPractica) && (!(*itAviones)->estaColisionando())) {
            for (list<AvionEnemigo *>::iterator itEnemigos = this->enemigos.begin();
                 itEnemigos != this->enemigos.end(); itEnemigos++) {
                if ((*itAviones)->getColisionable()->colisiona((*itEnemigos)->getColisionable()) && (*itAviones)->getVidas() != 0) {
                    if(!(*itEnemigos)->estaColisionando()){
                           if((*itEnemigos)->getTipoAvion() == TIPO_AVION_ESCUADRON){
                               (*itAviones)->sumarPuntos((*itEnemigos)->estallar() + this->validarBonificacionEscuadron((*itEnemigos), (*itAviones)->getNumeroAvion()));

                               (*itAviones)->colisionar();
                           }
                            (*itAviones)->sumarPuntos((*itEnemigos)->estallar());
                            // Acá sumó puntos. Me fijo el estado de las cosas.
                            (*itAviones)->colisionar();

                    }
                }
            }
        }
    }

    for(list<Avion*>::iterator itAviones = this->aviones.begin(); itAviones != this->aviones.end(); itAviones++){
        if ((*itAviones)->getContadorTiempoInmunidad() == 0 && (!this->modoPractica) && (!(*itAviones)->estaColisionando())) {
            for (list<DisparoEnemigo *>::iterator itDisparosEnemigos = this->disparosEnemigos.begin();
                 itDisparosEnemigos != this->disparosEnemigos.end(); itDisparosEnemigos++) {
                if ((*itAviones)->getColisionable()->colisiona((*itDisparosEnemigos)->getColisionable()) && (*itAviones)->getVidas() != 0) {
                    (*itAviones)->colisionar();
                    (*itDisparosEnemigos)->colisionar();
                }
            }
        }
    }

    int nroAvion = 1;
    for(list<Avion*>::iterator itAviones = this->aviones.begin(); itAviones != this->aviones.end(); itAviones++){
        if ((*itAviones)->getContadorTiempoInmunidad() == 0 && (!(*itAviones)->estaColisionando())){
            for(list<PowerUp*>::iterator itPowerUps = this->powerUps.begin(); itPowerUps != this->powerUps.end(); itPowerUps++){
                if((*itAviones)->getColisionable()->colisiona((*itPowerUps)->getColisionable())){
                    if ((*itPowerUps)->getEstadoAnimacion() < POWER_UP_COLISIONADO){
                        (*itPowerUps)->colisionar();
                        aplicarPowerUp(*itPowerUps,*itAviones);
                    }
                }
            }
        }
        nroAvion++;
    }
}

void EscenarioJuego::crearPowerUpBonus(float posX, float posY, int valor){
    PowerUp* unPowerUpBonus = new PowerUpBonificacion1500(posX,posY,VALOR_POWERUP_1500);
    powerUps.push_back(unPowerUpBonus);
}

void EscenarioJuego::aplicarPowerUp(PowerUp* powerUp, Avion* avion){
    if((powerUp->getTipoPowerUp() == TIPO_POWERUP_BONIFICACION)||(powerUp->getTipoPowerUp() == TIPO_POWERUP_BONIFICACION_1500)){
        int valorBonus = powerUp->getValor();
        avion->sumarPuntos(valorBonus);
    }
    if(powerUp->getTipoPowerUp() == TIPO_POWERUP_DESTRUIR_ENEMIGOS){
        list<AvionEnemigo*> listaEnemigos = this->getEnemigos();
        int sumaPuntaje = 0;
        for (list<AvionEnemigo *>::iterator itEnemigos = this->enemigos.begin(); itEnemigos != this->enemigos.end(); itEnemigos++) {
            (*itEnemigos)->setVidasEnUno();
            sumaPuntaje += (*itEnemigos)->estallar();
        }
        avion->sumarPuntos(sumaPuntaje);
    }
    if(powerUp->getTipoPowerUp() == TIPO_POWERUP_DOS_AMETRALLADORAS){
        avion->setPowerUpAmetralladoras();
    }
    if(powerUp->getTipoPowerUp() == TIPO_POWERUP_AVIONES_SECUNDARIOS){
        avion->setPowerUpAvionesSecundarios();
    }
}

void EscenarioJuego::proyectarDisparos(float timeStep) {
    for(list<Disparo*>::iterator itDisparos = this->disparos.begin(); itDisparos != this->disparos.end(); itDisparos++){
        (*itDisparos)->getColisionable()->proyectarColisionable(timeStep);
    }
}

list< pair<int,vector<int>> > EscenarioJuego::getPuntajes() {
    list<pair<int,vector<int>> > equipoPuntaje;
    for (unsigned int i = 0; i < equipos.size(); ++i) {
        set<int>::iterator it;
        for (it = equipos[i].begin(); it != equipos[i].end(); ++it) {
            pair<int,vector<int>> par;
            par.first = *it;
            cout << "nroavion en escenario: " << *it << endl;
            Avion * avionActual = avion(*it);
            par.second.push_back(i);
            par.second.push_back(avionActual->getPuntaje());
            par.second.push_back(avionActual->getCantidadDisparos());
            par.second.push_back(avionActual->getCantidadAciertos());
            par.second.push_back(avionActual->getPorcentajeAciertos());
            equipoPuntaje.push_back(par);
        }
    }

    return equipoPuntaje;
}

int EscenarioJuego::getNroEtapa() {
    return nroEtapaActual;
}

int EscenarioJuego::validarBonificacionEscuadron(AvionEnemigo * avionEnemigo, int nroAvion) {
    AvionDeEscuadron * avionDeEscuadron = dynamic_cast<AvionDeEscuadron*>(avionEnemigo);
    if( this->infoEscuadrones.find(avionDeEscuadron->getNumeroEscuadron()) == this->infoEscuadrones.end()) {
        pair<int, int> parAvionEscuadron;
        parAvionEscuadron.first = nroAvion;
        parAvionEscuadron.second = 1;
        this->infoEscuadrones.insert(make_pair(avionDeEscuadron->getNumeroEscuadron(),parAvionEscuadron));
        return 0;
    } else {
        map<int, pair<int, int>>::iterator infoEscuadron = this->infoEscuadrones.find(avionDeEscuadron->getNumeroEscuadron());
        if((*infoEscuadron).second.first == -1){
            return 0;
        }
        if((*infoEscuadron).second.first != nroAvion){
            (*infoEscuadron).second.first = -1;
            return 0;
        } else { ;
            (*infoEscuadron).second.second++;;
            if((*infoEscuadron).second.second == 5){
                this->infoEscuadrones.erase(infoEscuadron);
                return 1000;
            } else {
                return 0;
            }
        }

    }
}

void EscenarioJuego::iniciarModoPractica() {
    this->modoPractica = true;
}
