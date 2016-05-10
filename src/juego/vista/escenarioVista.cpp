#include "escenarioVista.hpp"
using namespace std;

EscenarioVista::EscenarioVista(string infoEscenario){
    this->ancho = Decodificador::popInt(infoEscenario);
    this->alto = Decodificador::popInt(infoEscenario);
    this->pathImagen = Decodificador::popIdImg(infoEscenario);
    this->ventana = new Ventana(this->ancho, this->alto);
    this->scrollingOffset = 0;
    this->inicializarComponentes(infoEscenario);
    this->fondo = new Figura();
    this->preloop();
}

// Provisorio. Carga todas las cosas. Anterior al loop.
void EscenarioVista::preloop(){
    ventana->iniciar();
    cargarFondo();
    renderizarFondo(scrollingOffset);
    SDL_RenderPresent(ventana->getVentanaRenderer());
    cargarVistasAviones();
    cargarVistasElementos();
    cargarVistaDisparos();
    SDL_SetRenderDrawColor(getVentana()->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear((getVentana()->getVentanaRenderer()));
}

void EscenarioVista::inicializarComponentes(string infoEscenario){
    int cantAviones = Decodificador::popInt(infoEscenario);
    for(int i = 0; i < cantAviones; i++){
        string avion = Decodificador::popAvionInicial(infoEscenario);
        this->agregarAvionVista(avion);
    }
    int cantElementos = Decodificador::popInt(infoEscenario);
    for(int i = 0; i < cantElementos; i++){
        string elemento = Decodificador::popElementoInicial(infoEscenario);
        this->agregarElementoVista(elemento);
    }
    string disparo = Decodificador::popDisparoInicial(infoEscenario);
    this->agregarDisparoVista(disparo);
}

void EscenarioVista::actualizarComponentes(string infoActualizacion) {
    float offset = Decodificador::popFloat(infoActualizacion);
    this->actualizar(offset);
    list<AvionVista*>::iterator itAvion;
    for(itAvion = this->getAviones().begin(); itAvion != this->getAviones().end(); itAvion++){
        string avion = Decodificador::popAvion(infoActualizacion);
        (*itAvion)->actualizar(avion);
    }
    list<ElementoVista*>::iterator itElemento;
    for(itElemento = this->getElementos().begin(); itElemento != this->getElementos().end(); itElemento++){
        string elemento = Decodificador::popElemento(infoActualizacion);
        (*itElemento)->actualizar(elemento);
    }
    list<disparo> disparos;
    for (int i = Decodificador::popInt(infoActualizacion); i > 0; i--){
        // cout << "hay disparos" << endl;
        disparo unDisparo;
        unDisparo.posX = Decodificador::popFloat(infoActualizacion);
        unDisparo.posY = Decodificador::popFloat(infoActualizacion);
        disparos.push_front(unDisparo);
    }

    // TODO chequear...
    //TODO saqué esta validación porque sino no se seteaba cuando no había disparos y traia problemas en el reset
    //if (disparos.size() > 0) {
        this->setDisparos(disparos);
    //}
}

EscenarioVista::~EscenarioVista(){}

void* EscenarioVista::mainLoop_th(void* THIS){
    EscenarioVista* escenario = (EscenarioVista*) THIS;
    SDL_Event e;
    while(escenario->getActivo()){
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT )
            {
                escenario->setInactivo();
            }
            escenario->pushEvento(e);
        }
        //TODO puede fallar mutex.
        SDL_SetRenderDrawColor(escenario->getVentana()->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(escenario->getVentana()->getVentanaRenderer());
        escenario->renderizarFondo(escenario->scrollingOffset);
        escenario->renderizarFondo(escenario->scrollingOffset - escenario->fondo->getHeight());
        escenario->renderizarElementos();
        escenario->renderizarAviones();
        escenario->renderizarDisparos();
        SDL_RenderPresent(escenario->getVentana()->getVentanaRenderer());
    }
    cout << "Finalizó el ciclo de render." << endl;
    escenario->cerrar();
    pthread_exit(NULL);
}

bool EscenarioVista::getActivo(){
  return this->activo;
}

int EscenarioVista::mainLoop(){
	pthread_create(&mainLoopThread, NULL, mainLoop_th, (void*)this);
  return 1;
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

void EscenarioVista::setActivo(){
    this->activo = true;
}

void EscenarioVista::setInactivo(){
    this->activo = false;
}

void EscenarioVista::cerrar(){
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

void EscenarioVista::setScrollingOffset(float scrollingOffset){
    this->scrollingOffset = scrollingOffset;
}

/* Inicializacion de elementos internos del escenario */

void EscenarioVista::agregarElementoVista(string codigo){
    //Agrega el elemento a la lista.
    ElementoVista* elementoVista = new ElementoVista(codigo);
    this->elementos.push_back(elementoVista);
}

void EscenarioVista::agregarAvionVista(string infoAvion){
    AvionVista* avionVista = new AvionVista(infoAvion);
    this->aviones.push_back(avionVista);
}

void EscenarioVista::agregarDisparoVista(string pathSprite){
    this->disparoVista = new DisparoVista(pathSprite);
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
    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        ElementoVista* elementoVista = *iterador;
        this->cargarElemento(elementoVista, ventana->getVentanaRenderer());
    }
}

void EscenarioVista::cargarVistaDisparos() {
    this->disparoVista->cargarImagen(this->ventana->getVentanaRenderer());
}

void EscenarioVista::cargarFondo(){
    this->fondo->loadFromFile(this->pathImagen, this->ventana->getVentanaRenderer());
}

void EscenarioVista::cargarAvion(AvionVista* avionVista, SDL_Renderer* renderer, int numeroJugador){
    avionVista->cargarImagen(renderer, numeroJugador);
}

void EscenarioVista::cargarElemento(ElementoVista* elementoVista, SDL_Renderer* renderer){
    elementoVista->cargarImagen(renderer);
}

/* Renderizaciones */

void EscenarioVista::renderizarElementos(){
    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        ElementoVista* elementoVista = *iterador;
        elementoVista->render(this->ventana->getVentanaRenderer());
    }
}

void EscenarioVista::renderizarAviones(){
    for(list<AvionVista*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        AvionVista* avion = *iterador;
        avion->render(this->ventana->getVentanaRenderer());
    }
}

void EscenarioVista::renderizarFondo(float y) {
    pthread_mutex_lock(&mutexActualizar);
    this->fondo->render(0,(int)y,this->ventana->getVentanaRenderer(), NULL);
    pthread_mutex_unlock(&mutexActualizar);
}

void EscenarioVista::renderizarDisparos(){
    pthread_mutex_lock(&mutexDisparos);
    for(list<disparo>::iterator iterador = this->disparos.begin(); iterador != this->disparos.end(); ++iterador){
        disparo disparo1 = *iterador;
        disparoVista->render(disparo1.posX, disparo1.posY, this->ventana->getVentanaRenderer());
    }
    pthread_mutex_unlock(&mutexDisparos);
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
