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
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 )
    {
        if((this->estadoAnimacion < LOOP_ETAPA_1)){
            switch( evento )
            {
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
                    this->disparos.push_front(new Disparo(this->posX + (this->getAncho() / 2.f) - (this->getAnchoDisparo() / 2.f), this->posY - this->getAltoDisparo(), this->velocidadDisparos, this->idSpriteDisparo, renderer));
                    break;
                case SDLK_RETURN:
                    this->estadoAnimacion = 3;
                    break;
            }
        }
    }
        //If a key was released
    else if( evento.type == SDL_KEYUP && evento.key.repeat == 0 )
    {
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP:
                this->velocidadY += this->velocidad;
                break;
            case SDLK_DOWN:
                this->velocidadY -= this->velocidad;
                break;
            case SDLK_LEFT:
                this->velocidadX += this->velocidad;
                if( !currentKeyStates[ SDL_SCANCODE_RIGHT ])
                    this->estadoAnimacion = 0;
                break;
            case SDLK_RIGHT:
                this->velocidadX -= this->velocidad;
                if( !currentKeyStates[ SDL_SCANCODE_LEFT ])
                    this->estadoAnimacion = 0;
                break;
        }
    }
}

void Avion::mover(float timeStep){
    if(this->estadoAnimacion < 3) {
        this->posX += this->velocidadX * timeStep;
        if( this->posX < 0 ){
            this->posX = 0;
        }else if( this->posX + 80 > 800){
            this->posX = 720;
        }
        this->posY += this->velocidadY * timeStep;
        if( this->posY < 0 ){
            this->posY = 0;
        } else if ( this->posY + 80 > 800){
            this->posY = 720;
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
