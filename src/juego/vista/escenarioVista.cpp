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
    while(infoActualizacion != ""){
        disparo unDisparo;
        unDisparo.posX = Decodificador::popFloat(infoActualizacion);
        unDisparo.posY = Decodificador::popFloat(infoActualizacion);
        disparos.push_front(unDisparo);
    }
    this->setDisparos(disparos);
}

EscenarioVista::~EscenarioVista(){}

int EscenarioVista::mainLoop(){
    this->ventana->iniciar();
    this->cargarFondo();
    pthread_mutex_lock(&mutexActualizar);
    this->renderizarFondo(this->scrollingOffset);
    pthread_mutex_unlock(&mutexActualizar);
    SDL_RenderPresent(this->ventana->getVentanaRenderer());
    this->cargarVistasAviones();
    this->cargarVistasElementos();
    SDL_Event e;
    Temporizador temporizador;
    SDL_SetRenderDrawColor(ventana->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(ventana->getVentanaRenderer());
    this->setActivo();
    while(this->activo){
        temporizador.comenzar();
        pthread_mutex_lock(&mutexActualizar);
        this->renderizarFondo(this->scrollingOffset);
        this->renderizarFondo(this->scrollingOffset - this->fondo->getHeight());
        pthread_mutex_unlock(&mutexActualizar);
        this->renderizarElementos();
        this->renderizarAviones();
        pthread_mutex_lock(&mutexDisparos);
        this->renderizarDisparos();
        pthread_mutex_unlock(&mutexDisparos);
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
    return 1;
}

void EscenarioVista::setActivo(){
    this->activo = true;
}

void EscenarioVista::setInactivo(){
    this->activo = false;
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
    this->fondo->render(0,(int)y,this->ventana->getVentanaRenderer(), NULL);
}

void EscenarioVista::renderizarDisparos(){
    for(list<disparo>::iterator iterador = this->disparos.begin(); iterador != this->disparos.end(); ++iterador){
        disparo disparo1 = *iterador;
        disparoVista->render(disparo1.posX, disparo1.posY, this->ventana->getVentanaRenderer());
    }
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
