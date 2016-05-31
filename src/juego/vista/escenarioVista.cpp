#include "escenarioVista.hpp"
using namespace std;

EscenarioVista::EscenarioVista(string infoEscenario){
    this->anchoVentana = Decodificador::popInt(infoEscenario);
    this->altoVentana = Decodificador::popInt(infoEscenario);
    this->ventana = new Ventana(this->anchoVentana, this->altoVentana);

    this->ancho = Decodificador::popInt(infoEscenario);
    this->alto = Decodificador::popInt(infoEscenario);

    this->pathImagen = Decodificador::popIdImg(infoEscenario);

    this->scrollingOffset = 0;
    this->contadorSonido = 0;
    this->fondo = new Figura();
    this->soundBoard = new SoundBoard();
    this->soundBoard->inicializar();
    this->inicializarComponentes(infoEscenario);
    this->puntaje = 0;
}

void EscenarioVista::inicializarComponentes(string infoEscenario) {
    int cantAviones = Decodificador::popInt(infoEscenario);
    for(int i = 0; i < cantAviones; i++) {
        string avion = Decodificador::popAvionInicial(infoEscenario);
        this->agregarAvionVista(avion);
    }
    int cantEtapas = Decodificador::popInt(infoEscenario);
    for (int i = 0; i < cantEtapas; ++i) {
        int cantElementos = Decodificador::popInt(infoEscenario);
        EtapaVista * etapaVista = new EtapaVista();

        for(int j = 0; j < cantElementos; ++j) {
            string elemento = Decodificador::popElementoInicial(infoEscenario);
            etapaVista->agregarElementoVista(elemento);
        }
        etapas.push_back(etapaVista);
    }
    itEtapa = etapas.begin();
    string disparo = Decodificador::popDisparoInicial(infoEscenario);
    this->agregarDisparoVista(disparo);
    this->agregarVistasEnemigos();
    this->nroAvion = Decodificador::popInt(infoEscenario);

    if (infoEscenario.length() != 0) {
        cout << "Advertencia: el mensaje de inicialización del escenario todavía tiene bytes sin usar." << endl;
    }

    cout << "El número del avión es " << nroAvion << endl;
}

int EscenarioVista::comenzarEtapa() {
    this->activar();
    this->scrollingOffset = 0;
    this->elementos = etapaActual()->getElementos();
    cout << "se comienza una etapa con " << elementos.size() << " elementos." << endl;
    return this->mainLoop();
}

void EscenarioVista::avanzarEtapa() {
    desactivar();
    ++itEtapa;
}

EtapaVista* EscenarioVista::etapaActual() {
    return *itEtapa;
}

bool EscenarioVista::quedanEtapas() {
    return itEtapa != etapas.end();
}


void EscenarioVista::manejarEvento(int evento) {
    switch (evento) {
        case AVANZAR_ETAPA:
            avanzarEtapa();
            Logger::instance()->logInfo("Se avanza de etapa.");
            break;
        default:
            Logger::instance()->logWarning("El evento que recibió el cliente no existe.");
            break;
    }
}

void EscenarioVista::actualizarComponentes(string infoActualizacion) {
    float offset = Decodificador::popFloat(infoActualizacion);
    this->actualizar(offset);
    list<AvionVista*>::iterator itAvion;
    for(itAvion = this->getAviones().begin(); itAvion != this->getAviones().end(); itAvion++){
        string avion = Decodificador::popAvion(infoActualizacion);
        int sonido = (*itAvion)->actualizar(avion);
        if (sonido == CODIGO_SONIDO_DISPARO){
            if (this->contadorSonido == 0){
                this->contadorSonido = CONTADOR_SONIDO_DISPARO_INICIAL;
                this->soundBoard->reproducirDisparo();
            }
        } else if (sonido == CODIGO_SONIDO_LOOP) {
            this->soundBoard->reproducirLoop();
        }
        if (this->contadorSonido > 0){
            this->contadorSonido = this->contadorSonido - 1;
        }
    }
    list<ElementoVista*>::iterator itElemento;
    for(itElemento = this->getElementos().begin(); itElemento != this->getElementos().end(); itElemento++){
        string elemento = Decodificador::popElemento(infoActualizacion);
        (*itElemento)->actualizar(elemento);
    }
    list<disparo> disparos;
    int cantDisparos = Decodificador::popInt(infoActualizacion);
    if (cantDisparos != 0) {
    }
    for (int i = 0; i < cantDisparos; ++i) {
        disparo unDisparo;
        unDisparo.posX = Decodificador::popFloat(infoActualizacion);
        unDisparo.posY = Decodificador::popFloat(infoActualizacion);
        disparos.push_front(unDisparo);
    }

    this->setDisparos(disparos);
    int cantEnemigos = Decodificador::popInt(infoActualizacion);
    list<enemigo> enemigos;
    for (int i = 0; i < cantEnemigos; ++i) {
        enemigo unEnemigo;
        unEnemigo.posX = Decodificador::popFloat(infoActualizacion);
        unEnemigo.posY = Decodificador::popFloat(infoActualizacion);
        unEnemigo.estadoAnimacion = Decodificador::popInt(infoActualizacion);
        unEnemigo.tipoEnemigo = Decodificador::popInt(infoActualizacion);
        enemigos.push_front(unEnemigo);
    }
    this->setEnemigos(enemigos);
    this->puntaje = Decodificador::popInt(infoActualizacion);


    if (infoActualizacion.size() != 0) {
        cout << "el mensaje queda con " <<  infoActualizacion.size() << " bytes luego de actualizar." << endl;
    }
}

EscenarioVista::~EscenarioVista(){}

// Carga todas las cosas. Anterior al loop.
void EscenarioVista::preloop(){
    ventana->iniciar();
    cargarFondo();
    cargarVistasAviones();
    cargarVistasElementos();
    cargarVistaDisparos();
    cargarVistaEnemigos();
    cargarSonidos();
}

int EscenarioVista::mainLoop(){
    cout << "se entra al mainLoop" << endl;
    SDL_Event e;
    this->soundBoard->toggleMusica();
    while(this->getActivo()){
        while ( SDL_PollEvent( &e ) != 0 ) {
            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_CLOSE){
                    cout << "Evento de cierre" << endl;
                    this->desactivar();
                    return CERRAR;
                }
            } else if (e.key.keysym.sym == SDLK_x) {
                cout << "Se apretó x" << endl;
                this->desactivar();
                return CERRAR;
            }
            this->pushEvento(e);
        }
        // TODO por ahí conviene agregar un mutex.
        SDL_SetRenderDrawColor(this->getVentana()->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(this->getVentana()->getVentanaRenderer());
        this->renderizarFondo(this->scrollingOffset);
        this->renderizarFondo(this->scrollingOffset - this->fondo->getHeight());
        this->renderizarElementos();
        this->renderizarAviones();
        this->renderizarDisparos();
        this->renderizarEnemigos();
        SDL_RenderPresent(this->getVentana()->getVentanaRenderer());
    }
    cout << "el getActivo es " << (getActivo()?" true":" false") << endl;
    cout << "Finalizó el ciclo de render." << endl;
    //cerrar();
    return CONTINUAR;
}

void EscenarioVista::pushEvento(SDL_Event evento){
    if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 )
    {
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP:
                this->colaEventos.push((int)ARRIBA_PRESIONA);
                break;
            case SDLK_DOWN:
                this->colaEventos.push((int)ABAJO_PRESIONA);
                break;
            case SDLK_LEFT:
                this->colaEventos.push((int)IZQUIERDA_PRESIONA);
                break;
            case SDLK_RIGHT:
                this->colaEventos.push((int)DERECHA_PRESIONA);
                break;
            case SDLK_SPACE:
                this->colaEventos.push((int)PRESIONA_ESPACIO);
                break;
            case SDLK_RETURN:
                this->colaEventos.push((int)PRESIONA_ENTER);
                break;
            case SDLK_r:
                this->colaEventos.push((int)PRESIONA_R);
                break;
            case SDLK_x:
                this->colaEventos.push((int)PRESIONA_X);
            case SDLK_m:
                this->soundBoard->toggleMusica();
                break;
        }
    } else if( evento.type == SDL_KEYUP && evento.key.repeat == 0 ) {
        switch( evento.key.keysym.sym )
            {
                case SDLK_UP:
                    this->colaEventos.push((int)ARRIBA_SUELTA);
                    break;
                case SDLK_DOWN:
                    this->colaEventos.push((int)ABAJO_SUELTA);
                    break;
                case SDLK_LEFT:
                    this->colaEventos.push((int)IZQUIERDA_SUELTA);
                    break;
                case SDLK_RIGHT:
                    this->colaEventos.push((int)DERECHA_SUELTA);
                    break;
            }
    }
}

int EscenarioVista::popEvento() {
    if(!colaEventos.vacia()){
        return colaEventos.pop();
    } else{
        return EVENTO_VACIO;
    }
}

void EscenarioVista::activar() {
    this->activo = true;
}

void EscenarioVista::desactivar() {
    this->activo = false;
    colaEventos.avisar();
}

void EscenarioVista::cerrar() {
    this->fondo->free();

    for(list<AvionVista*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        AvionVista* avionVista = *iterador;
        avionVista->cerrar();
    }

    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        ElementoVista* elementoVista = *iterador;
        elementoVista->cerrar();
    }
    this->disparoVista->cerrar();
    this->ventana->cerrar();
}

void EscenarioVista::setDisparos(list<disparo> disparosParam){
    pthread_mutex_lock(&this->mutexDisparos);
    this->disparos = disparosParam;
    pthread_mutex_unlock(&this->mutexDisparos);
}

void EscenarioVista::setEnemigos(list<enemigo> enemigosParam){
    pthread_mutex_lock(&this->mutexEnemigos);
    this->enemigos = enemigosParam;
    pthread_mutex_unlock(&this->mutexEnemigos);
}

void EscenarioVista::setScrollingOffset(float scrollingOffset){
    this->scrollingOffset = scrollingOffset;
}

/* Inicializacion de elementos internos del escenario */

void EscenarioVista::agregarAvionVista(string infoAvion){
    AvionVista* avionVista = new AvionVista(infoAvion);
    this->aviones.push_back(avionVista);
}

void EscenarioVista::agregarDisparoVista(string pathSprite){
    this->disparoVista = new DisparoVista(pathSprite);
}

void EscenarioVista::agregarVistasEnemigos(){
    this->enemigoPequenio = new EnemigoPequenio();
    this->enemigoDeEscuadron = new EnemigoDeEscuadron();
    this->enemigoMediano = new EnemigoMediano();
    this->enemigoGrande = new EnemigoGrande();
}

void EscenarioVista::cargarVistasAviones(){
    int numeroJugador = 1;
    for(list<AvionVista*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        AvionVista* avionVista = *iterador;
        this->cargarAvion(avionVista, ventana->getVentanaRenderer(), numeroJugador);
        numeroJugador++;
    }
}


void EscenarioVista::cargarVistasElementos(){
    // Cargo imágenes de todas las etapas.
    list<EtapaVista*>::iterator i;
    for (i = etapas.begin(); i != etapas.end(); ++i) {
        EtapaVista * etapa = *i;
        list<ElementoVista*>::iterator j;
        list<ElementoVista*> elementos = etapa->getElementos();
        for (j = elementos.begin(); j != elementos.end(); ++j){
            this->cargarElemento(*j, ventana->getVentanaRenderer());
        }
    }
}

void EscenarioVista::cargarVistaDisparos() {
    this->disparoVista->cargarImagen(this->ventana->getVentanaRenderer());
}

void EscenarioVista::cargarVistaEnemigos() {
    this->enemigoPequenio->cargarImagen(this->ventana->getVentanaRenderer());
    this->enemigoDeEscuadron->cargarImagen(this->ventana->getVentanaRenderer());
    this->enemigoMediano->cargarImagen(this->ventana->getVentanaRenderer());
    this->enemigoGrande->cargarImagen(this->ventana->getVentanaRenderer());

}

void EscenarioVista::cargarFondo(){
    if(!this->fondo->loadFromFile(this->pathImagen, this->ventana->getVentanaRenderer())){
        this->fondo->loadFromFile(FONDO_POR_DEFECTO, this->ventana->getVentanaRenderer());
    }
}

void EscenarioVista::cargarAvion(AvionVista* avionVista, SDL_Renderer* renderer, int numeroJugador){
    avionVista->cargarImagen(renderer, numeroJugador);
}

void EscenarioVista::cargarElemento(ElementoVista* elementoVista, SDL_Renderer* renderer){
    elementoVista->cargarImagen(renderer);
}

void EscenarioVista::cargarSonidos() {
    this->soundBoard->cargarSonidos();
}

/* Renderizaciones */

void EscenarioVista::renderizarElementos(){
    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        ElementoVista* elementoVista = *iterador;
        elementoVista->render(this->ventana->getVentanaRenderer());
    }
}

void EscenarioVista::renderizarAviones() {
    list<AvionVista*>::iterator iterador;
    AvionVista* avionDelCliente;

    int i = 0;
    for(iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador) {
        ++i;
        // Primero dibujamos los aviones que no le correspondan a este cliente.
        if (i != nroAvion) {
            AvionVista* avion = *iterador;
            avion->render(this->ventana->getVentanaRenderer());
        } else {
            avionDelCliente = *iterador;
        }
    }
    // Último hay que dibujar el del nroAvion, para que esté arriba.
    avionDelCliente->render(this->ventana->getVentanaRenderer());
}

void EscenarioVista::renderizarFondo(float y) {
    pthread_mutex_lock(&mutexActualizar);
    this->fondo->render(0,(int)y,this->ventana->getVentanaRenderer(), NULL);
    pthread_mutex_unlock(&mutexActualizar);
}

void EscenarioVista::renderizarDisparos(){
    pthread_mutex_lock(&mutexDisparos);
    for(list<disparo>::iterator iterador = this->disparos.begin(); iterador != this->disparos.end(); ++iterador) {
        disparo disparo1 = *iterador;
        disparoVista->render(disparo1.posX, disparo1.posY, this->ventana->getVentanaRenderer());
    }
    pthread_mutex_unlock(&mutexDisparos);
}

void EscenarioVista::renderizarEnemigos(){
    pthread_mutex_lock(&mutexEnemigos);
    for(list<enemigo>::iterator iterador = this->enemigos.begin(); iterador != this->enemigos.end(); ++iterador) {
        enemigo enemigo1 = *iterador;

        if (enemigo1.tipoEnemigo == TIPO_AVION_PEQUENIO)
            this->enemigoPequenio->render(enemigo1.posX, enemigo1.posY, enemigo1.estadoAnimacion, this->ventana->getVentanaRenderer());
        else if (enemigo1.tipoEnemigo == TIPO_AVION_ESCUADRON)
            this->enemigoDeEscuadron->render(enemigo1.posX, enemigo1.posY, enemigo1.estadoAnimacion, this->ventana->getVentanaRenderer());
        else if (enemigo1.tipoEnemigo == TIPO_AVION_MEDIANO)
            this->enemigoMediano->render(enemigo1.posX, enemigo1.posY, enemigo1.estadoAnimacion, this->ventana->getVentanaRenderer());
        else
            this->enemigoGrande->render(enemigo1.posX, enemigo1.posY, enemigo1.estadoAnimacion, this->ventana->getVentanaRenderer());
    }
    pthread_mutex_unlock(&mutexEnemigos);
}

void EscenarioVista::actualizar(float offset) {
    pthread_mutex_lock(&this->mutexActualizar);
    this->scrollingOffset = offset;
    pthread_mutex_unlock(&this->mutexActualizar);

}

/* Getters */

int EscenarioVista::getAncho(){
    return this->ancho;
}

int EscenarioVista::getAlto(){
    return this->alto;
}

list<AvionVista*>& EscenarioVista::getAviones(){
    return this->aviones;
}

list<ElementoVista*>& EscenarioVista::getElementos(){
    return this->elementos;
}

Figura* EscenarioVista::getFondo(){
    return this->fondo;
}

Ventana* EscenarioVista::getVentana(){
    return this->ventana;
}

float EscenarioVista::getScrollingOffset(){
    return this->scrollingOffset;
}

bool EscenarioVista::getActivo(){
  return this->activo;
}
