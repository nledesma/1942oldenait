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

int EscenarioVista::iniciar(){
    this->ventana->iniciar();
    this->cargarFondo();
    this->renderizarFondo(this->scrollingOffset);
    SDL_RenderPresent(this->ventana->getVentanaRenderer());
    this->cargarVistasAviones();
    this->cargarVistasElementos();
    bool quit = false;
    SDL_Event e;
    Temporizador temporizador;
    while(!quit){
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            this->getAviones().front()->manejarEvento(e, ventana->getVentanaRenderer());
        }
        temporizador.comenzar();
        SDL_SetRenderDrawColor(ventana->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(ventana->getVentanaRenderer());
        this->fondo->render(0,0,ventana->getVentanaRenderer(), NULL);
        //Render background
        this->renderizarFondo(this->scrollingOffset);
        this->renderizarFondo(this->scrollingOffset - this->fondo->getWidth());

        this->renderizarElementos();
        this->renderizarAviones();
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
    return 1;
}

/* Inicializacion de elementos internos del escenario */

void EscenarioVista::agregarElementoVista(float posX, float posY, string elementoSpriteId){
    //Agrega el elemento a la lista.
    ElementoVista* elementoVista = new ElementoVista(posX, posY, elementoSpriteId);
    this->elementos.push_back(elementoVista);
}

void EscenarioVista::agregarAvionVista(float posX, float posY, string pathSprite){
    AvionVista* avionVista = new AvionVista( posX, posY, pathSprite);
    this->aviones.push_back(avionVista);
}

void EscenarioVista::cargarVistasAviones(){
    string path;
    int numeroJugador = 1;
    for(list<AvionVista*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        AvionVista* avionVista = *iterador;
        this->cargarAvion(avionVista, ventana->getVentanaRenderer(), numeroJugador);
        numeroJugador++;
    }

}

void EscenarioVista::cargarVistasElementos(){
    string path;
    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        path = (elementoVista->getSpriteId() + ".bmp").c_str();
        this->cargarElementoVista(elementoVista, ventana->getVentanaRenderer(), path);
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