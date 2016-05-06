#include "avion.hpp"

using namespace std;

Avion::Avion(float posX, float posY, float velocidad, float velocidadDisparos){
    this->posX = posX;
    this->posY = posY;
    this->velocidadX = 0;
    this->velocidadY = 0;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->contador = CONTADOR_INICIAL;
    this->estadoAnimacion = ESTADO_NORMAL;
}
Avion::~Avion(){

}

void Avion::manejarEvento(int evento){
    /* Se realizan acciones de avión si el mismo no esta loopeando */
    if((this->estadoAnimacion < LOOP_ETAPA_1)) {
        switch (evento) {
            case ARRIBA_PRESIONA:
                this->velocidadY -= this->velocidad;
                break;
            case ABAJO_PRESIONA:
                this->velocidadY += this->velocidad;
                break;
            case IZQUIERDA_PRESIONA:
                this->velocidadX -= this->velocidad;
                this->estadoAnimacion = GIRANDO_IZQUIERDA;
                break;
            case DERECHA_PRESIONA:
                this->estadoAnimacion = GIRANDO_DERECHA;
                this->velocidadX += this->velocidad;
                break;
            case PRESIONA_ESPACIO:
                this->disparar();
                break;
            case PRESIONA_ENTER:
                this->estadoAnimacion = LOOP_ETAPA_1;
                break;
            case ARRIBA_SUELTA:
                this->velocidadY += this->velocidad;
                break;
            case ABAJO_SUELTA:
                this->velocidadY -= this->velocidad;
                break;
            case IZQUIERDA_SUELTA:
                this->velocidadX += this->velocidad;
                if (this->estadoAnimacion != GIRANDO_DERECHA)
                    this->estadoAnimacion = ESTADO_NORMAL;
                break;
            case DERECHA_SUELTA:
                this->velocidadX -= this->velocidad;
                if (this->estadoAnimacion != GIRANDO_IZQUIERDA)
                    this->estadoAnimacion = ESTADO_NORMAL;
                break;
        }
    }
}

void Avion::mover(float timeStep){
    if(this->estadoAnimacion < 3) {
        this->posX += this->velocidadX * timeStep;
        if( this->posX < 0 ){
            this->posX = 0;
        }else if( this->posX + this->getAncho() > ANCHO_ESCENARIO){
            this->posX = ANCHO_ESCENARIO - this->getAncho();
        }
        this->posY += this->velocidadY * timeStep;
        if( this->posY < 0 ){
            this->posY = 0;
        } else if ( this->posY + this->getAlto() > ALTO_ESCENARIO){
            this->posY = ALTO_ESCENARIO - this->getAlto();
        }
    } else {
        if(this->contador > 0) {
            this->contador --;
        } else {
            this->contador = 150;
            if(this->estadoAnimacion == 5) {
                this->estadoAnimacion = 0;
            } else {
                this->estadoAnimacion ++;
            }
        }
    }
}

/*
void Avion::moverDisparos(float timeStep){
    if(this->disparos.size() > 0){
        for(list<Disparo*>::iterator iterador = disparos.begin(); iterador != disparos.end(); iterador++){
            if((*iterador)->mover(timeStep) == 0){
                delete (*iterador);
                iterador = disparos.erase(iterador);
            }
        }
    }
}

void Avion::renderDisparos(SDL_Renderer * renderer){
    if(disparos.size() > 0 ){
        for(list<Disparo*>::iterator iterator = disparos.begin(); iterator != disparos.end(); iterator++){
            (*iterator)->render(renderer);
        }
    }
}

string Avion::getIdSprite(){
    return this->idSprite;
}

void Avion::setIdSprite(string idSprite){
    this->idSprite = idSprite;
}

int Avion::getVelocidadDesplazamiento(){
    return this->velocidadDesplazamiento;
}

void Avion::setVelocidadDesplazamiento(int velocidadDesplazamiento){
    this->velocidadDesplazamiento = velocidadDesplazamiento;
}

string Avion::getIdSpriteAnimacion(){
    return this->idSpriteAnimacion;
}

void Avion::setIdSpriteAnimacion(string idSpriteAnimacion){
    this->idSpriteAnimacion = idSpriteAnimacion;
}
list<Disparo*> Avion::getDisparos() {
    return this->disparos;
}

void Avion::setDisparos(list<Disparo*> unosDisparos) {
    this->disparos = unosDisparos;
}

int Avion::cargarImagen(string path, SDL_Renderer* renderer){
    if(!this->gAvionTextura->loadFromFile(path, renderer, 1)){
        cout << "Failed" << endl;
        //TODO usar una excepcion
        return 0;
    }
    this->render(renderer);
    return 1;
}

void Avion::render(SDL_Renderer* renderer){
    this->gAvionTextura->render((int)this->posX, (int)this->posY, renderer, &this->clipsAnimacion[this->estadoAnimacion]);
}

void Avion::cerrar(){
    this->gAvionTextura->free();
}

SDL_Renderer* Avion::getAvionRenderer(){
    return this->gAvionRenderer;
}

Figura* Avion::getAvionTextura(){
    return this->gAvionTextura;
}
*/
float Avion::getPosicionX(){
    return this->posX;
}
float Avion::getPosicionY(){
    return this->posY;
}

int Avion::getAncho(){
    return AVION_ANCHO;
}
int Avion::getAlto(){
    return AVION_ALTO;
}

int Avion::getAnchoDisparo(){
    return DISPARO_ANCHO;
}

int Avion::getAltoDisparo(){
    return DISPARO_ALTO;
}

int Avion::getEstadoAnimacion(){
    return this->estadoAnimacion;
}
