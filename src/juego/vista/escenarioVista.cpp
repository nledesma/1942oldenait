#include "escenarioVista.hpp"
using namespace std;

EscenarioVista::EscenarioVista(int ancho, int alto, string pathImagen){
    this->ancho = ancho;
    this->alto = alto;
    this->ventana = new Ventana(ancho, alto);
    this->fondo = new Figura();
    this->scrollingOffset = 0;
    this->pathImagen = pathImagen;
}

EscenarioVista::~EscenarioVista(){}

int EscenarioVista::iniciar(pthread_mutex_t mutexEscritura){
    this->ventana->iniciar();
    this->cargarFondo();
    this->renderizarFondo(this->scrollingOffset);
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
        pthread_mutex_lock(&mutexEscritura);
        this->renderizarFondo(this->scrollingOffset);
        this->renderizarFondo(this->scrollingOffset - this->fondo->getHeight());
        pthread_mutex_unlock(&mutexEscritura);
        this->renderizarElementos(mutexEscritura);
        this->renderizarAviones(mutexEscritura);
        this->renderizarDisparos(mutexEscritura);
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
    this->disparos = disparosParam;
}

void EscenarioVista::setScrollingOffset(float scrollingOffset){
    this->scrollingOffset = scrollingOffset;
}

/* Inicializacion de elementos internos del escenario */

void EscenarioVista::agregarElementoVista(float posX, float posY, string pathSprite){
    //Agrega el elemento a la lista.
    ElementoVista* elementoVista = new ElementoVista(posX, posY, pathSprite);
    this->elementos.push_back(elementoVista);
}

void EscenarioVista::agregarAvionVista(float posX, float posY, string pathSprite){
    AvionVista* avionVista = new AvionVista( posX, posY, pathSprite);
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

void EscenarioVista::renderizarElementos(pthread_mutex_t mutexEscritura){
    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        ElementoVista* elementoVista = *iterador;
        pthread_mutex_lock(&mutexEscritura);
        elementoVista->render(this->ventana->getVentanaRenderer());
        pthread_mutex_unlock(&mutexEscritura);
    }
}

void EscenarioVista::renderizarAviones(pthread_mutex_t mutexEscritura){
    for(list<AvionVista*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        AvionVista* avion = *iterador;
        pthread_mutex_lock(&mutexEscritura);
        avion->render(this->ventana->getVentanaRenderer());
        pthread_mutex_unlock(&mutexEscritura);
    }
}

void EscenarioVista::renderizarFondo(float y) {
    this->fondo->render(0,(int)y,this->ventana->getVentanaRenderer(), NULL);
}

void EscenarioVista::renderizarDisparos(pthread_mutex_t mutexEscritura){
    pthread_mutex_lock(&mutexEscritura);
    for(list<disparo>::iterator iterador = this->disparos.begin(); iterador != this->disparos.end(); ++iterador){
        disparo disparo1 = *iterador;
        disparoVista->render(disparo1.posX, disparo1.posY, this->ventana->getVentanaRenderer());
    }
    pthread_mutex_unlock(&mutexEscritura);
}

void EscenarioVista::crearEscenario(string infoEscenario){
    string escenario = Decodificador::popEscenarioInicial(infoEscenario);
    this->iniciarEscenario(escenario);
    string aviones = Decodificador::popCantidad(infoEscenario);
    int cantAviones = Decodificador::stringToInt(aviones);
    for(int i = 0; i < cantAviones; i++){
        string avion = Decodificador::popAvionInicial(infoEscenario);
        this->aviones.push_front(new AvionVista(avion));
    }
    string elementos = Decodificador::popCantidad(infoEscenario);
    int cantElementos = Decodificador::stringToInt(elementos);
    for(int i = 0; i < cantElementos; i++){
        string elemento = Decodificador::popElementoInicial(infoEscenario);
        this->elementos.push_front(new ElementoVista(elemento));
    }
    string disparo = Decodificador::popDisparoInicial(infoEscenario);
    this->disparoVista = new DisparoVista(disparo);
}

void EscenarioVista::iniciarEscenario(string infoEscenario){
    this->ancho = Decodificador::popInt(infoEscenario);
    this->alto = Decodificador::popInt(infoEscenario);
    this->pathImagen = infoEscenario;
}

void EscenarioVista::actualizar(string codigo) {
    memcpy((void*) &(this->scrollingOffset), (void*) &codigo[0], sizeof(float));
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
