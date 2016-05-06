#include "escenarioVista.hpp"
using namespace std;

EscenarioVista::EscenarioVista(int ancho, int alto){
    this->ancho = ancho;
    this->alto = alto;
    this->ventana = new Ventana(ancho, alto);
    this->fondo = new Figura();
    this->scrollingOffset = 0;
}

EscenarioVista::~EscenarioVista(){}

int EscenarioVista::iniciar(string path){
    this->ventana->iniciar();
    this->fondo->loadFromFile(path, this->ventana->getVentanaRenderer());
    this->fondo->render(0,0,this->ventana->getVentanaRenderer(), NULL);
    SDL_RenderPresent(this->ventana->getVentanaRenderer());
    incluirAviones();
    incluirElementos();

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

        float timeStep = temporizador.getTicks() / 1000.f;

        //Scroll background
        this->scrollingOffset = scrollingOffset + timeStep * this->velocidadDesplazamientoY;
        this->posicionY = this->posicionY + timeStep * this->velocidadDesplazamientoY;

        if(scrollingOffset > this->fondo->getWidth()){
            scrollingOffset = 0;
        }
        temporizador.comenzar();
        SDL_SetRenderDrawColor(ventana->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(ventana->getVentanaRenderer());
        this->fondo->render(0,0,ventana->getVentanaRenderer(), NULL);
        //Render background
        this->fondo->render(0, scrollingOffset, ventana->getVentanaRenderer(), NULL);
        this->fondo->render(0, scrollingOffset - this->fondo->getWidth(), ventana->getVentanaRenderer(), NULL);

        this->renderizarElementos(ventana->getVentanaRenderer());
        this->renderizarAviones(ventana->getVentanaRenderer());
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
    return 1;
}

/* Inicializacion de elementos internos del escenario */

void EscenarioVista::agregarElementoVista(string spriteId, float posX, float posY){
    //Agrega el elemento a la lista.
    Elemento* elemento = new Elemento(posX, posY, this->velocidadDesplazamientoY ,spriteId);
    this->elementos.push_back(elemento);
}

void EscenarioVista::agregarAvionVista(string avionSpriteId, string disparosSpriteId){
    AvionVista* avionVista = new AvionVista(avionSpriteId, "redLaserRay.bmp");
    this->aviones.push_back(avionVista);
}

void EscenarioVista::cargarVistasAviones(){
    string path;
    for(list<AvionVista*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        AvionVista* avionVista = *iterador;
        path = (avionVista->getIdSprite() + ".bmp").c_str();
        this->cargarAvionVista(avionVista, ventana->getVentanaRenderer(),path);
    }

}

void EscenarioVista::cargarVistasElementos(){
    string path;
    for(list<ElementoVista*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        ElementoVista* elementoVista = *iterador;
        path = (elemento->getSpriteId() + ".bmp").c_str();
        this->cargarElemento(elemento, ventana->getVentanaRenderer(),path);
        //this->cargarElemento(elemento2, ventana->getVentanaRenderer(), "asteroide.bmp");
    }
}

void EscenarioVista::cargarAvionVista(AvionVista* avionVista, SDL_Renderer* renderer, string path){
    avionVista->cargarImagen(path, renderer);
}

void EscenarioVista::cargarElementoVista(ElementoVista* elementoVista, SDL_Renderer* renderer, string path){
    elementoVista->cargarImagen(path ,renderer);
}

/* Renderizaciones */

void EscenarioVista::renderizarElementos(SDL_Renderer* renderer){
    for(list<Elemento*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
        Elemento* elemento = *iterador;
        elemento->render(renderer);
    }
}

void EscenarioVista::renderizarAviones(SDL_Renderer* renderer){
    for(list<Avion*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
        Avion* avion = *iterador;
        avion->render(renderer);
        avion->renderDisparos(renderer);
    }
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

const char* EscenarioVista::getFondoSprite(){
    const char* fondo = "galaxia";
    return fondo;
}