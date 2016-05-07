#include "avionVista.hpp"

//TODO ver de donde sacar las dimensiones del avion
AvionVista::AvionVista(float posX, float posY, string pathSprite){
    this->posX = posX;
    this->posY = posY;
    this->estadoAnimacion = ESTADO_NORMAL;
    this->pathSprite = pathSprite;
    this->figura = new Figura();

    //Avión en estado normal
    this->clipsAnimacion[ESTADO_NORMAL].x = 0;
    this->clipsAnimacion[ESTADO_NORMAL].y = 0;
    this->clipsAnimacion[ESTADO_NORMAL].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[ESTADO_NORMAL].h = ALTO_AVION_COMUN;

    //Avión moviéndose a la izquierda
    this->clipsAnimacion[GIRANDO_IZQUIERDA].x = 0 + ANCHO_AVION_COMUN;
    this->clipsAnimacion[GIRANDO_IZQUIERDA].y = 0;
    this->clipsAnimacion[GIRANDO_IZQUIERDA].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[GIRANDO_IZQUIERDA].h = ALTO_AVION_COMUN;

    //Avión moviéndose a la derecha
    this->clipsAnimacion[GIRANDO_DERECHA].x = 0 + ANCHO_AVION_COMUN * 2;
    this->clipsAnimacion[GIRANDO_DERECHA].y = 0;
    this->clipsAnimacion[GIRANDO_DERECHA].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[GIRANDO_DERECHA].h = ALTO_AVION_COMUN;

    //Primer sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_1].x = 0 + ANCHO_AVION_COMUN * 3;
    this->clipsAnimacion[LOOP_ETAPA_1].y = 0;
    this->clipsAnimacion[LOOP_ETAPA_1].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_1].h = ALTO_AVION_COMUN;

    //Segundo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_2].x = 0 + ANCHO_AVION_COMUN * 4;
    this->clipsAnimacion[LOOP_ETAPA_2].y = 0;
    this->clipsAnimacion[LOOP_ETAPA_2].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_2].h = ALTO_AVION_COMUN;

    //Tercer sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_3].x = 0;
    this->clipsAnimacion[LOOP_ETAPA_3].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_3].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_3].h = ALTO_AVION_COMUN;

}

void AvionVista::manejarEvento(SDL_Event evento){
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( evento.type == SDL_KEYDOWN && evento.key.repeat == 0 )
    {
        if((this->estadoAnimacion < 3)){
            switch( evento.key.keysym.sym )
            {
                case SDLK_UP:
                    this->cliente->enviarEvento(ARRIBA_PRESIONA);
                    break;
                case SDLK_DOWN:
                    this->cliente->enviarEvento(ABAJO_PRESIONA);
                    break;
                case SDLK_LEFT:
                    this->cliente->enviarEvento(IZQUIERDA_PRESIONA);
                    break;
                case SDLK_RIGHT:
                    this->cliente->enviarEvento(DERECHA_PRESIONA);
                    break;
                case SDLK_SPACE:
                    this->cliente->enviarEvento(PRESIONA_ESPACIO);
                    break;
                case SDLK_RETURN:
                    this->cliente->enviarEvento(PRESIONA_ENTER);
                    break;
            }
        }
    }
    else if( evento.type == SDL_KEYUP && evento.key.repeat == 0 )
    {
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP:
                this->cliente->enviarEvento(ARRIBA_SUELTA);
                break;
            case SDLK_DOWN:
                this->cliente->enviarEvento(ABAJO_SUELTA);
                break;
            case SDLK_LEFT:
                this->cliente->enviarEvento(IZQUIERDA_SUELTA);
                break;
            case SDLK_RIGHT:
                this->cliente->enviarEvento(DERECHA_SUELTA);
                break;
        }
    }
}

void AvionVista::cargarImagen(SDL_Renderer* renderer, int color){
    if(!this->figuraAvion->loadFromFile(this->pathSprite, renderer, color)){
        cout << "Failed" << endl;
        this->figuraAvion->loadFromFile((string) AvionVista::AVION_POR_DEFECTO, renderer, color);
    }
}

void AvionVista::render(SDL_Renderer* renderer){
    this->figuraAvion->render((int)this->posX, (int)this->posY, renderer, &this->clipsAnimacion[this->estadoAnimacion]);
}

void AvionVista::cerrar(){
    this->figuraAvion->free();
}

float AvionVista::getPosX(){
    return this->posX;
}

float AvionVista::getPosY(){
    return this->posY;
}

int AvionVista::getAncho() {
    return this->figura->getWidth();
}

int AvionVista::getAlto() {
    return this->figura->getHeight();
}

Figura* AvionVista::getFigura(){
    return this->figura;
}

int AvionVista::getEstadoAnimacion(){
    return this->estadoAnimacion;
}

void AvionVista::setPosX(float posX){
    this->posX = posX;
}

void AvionVista::setPosY(float posY){
    this->posY = posY;
}

void AvionVista::setFigura(Figura * figura){
    this->figura = figura;
}

void AvionVista::setEstadoAnimacion(int estadoAnimacion){
    this->estadoAnimacion = estadoAnimacion;
}
