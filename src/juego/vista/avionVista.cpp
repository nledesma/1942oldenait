#include "avionVista.hpp"

AvionVista::AvionVista(float posX, float posY, string pathSprite){
    this->iniciarAvion(posX, posY, pathSprite);
}

AvionVista::AvionVista(string infoAvion){
    float posX = Decodificador::popFloat(infoAvion);
    float posY = Decodificador::popFloat(infoAvion);
    this->iniciarAvion(posX, posY, infoAvion);
}

AvionVista::~AvionVista() { }

void AvionVista::iniciarAvion(float posX, float posY, string pathSprite){
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

    //Cuarto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_4].x = 0 + ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_4].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_4].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_4].h = ALTO_AVION_COMUN;

    //Quinto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_5].x = 0 + ANCHO_AVION_COMUN * 2;
    this->clipsAnimacion[LOOP_ETAPA_5].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_5].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_5].h = ALTO_AVION_COMUN;

    //Sexto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_6].x = 0 + ANCHO_AVION_COMUN * 3;
    this->clipsAnimacion[LOOP_ETAPA_6].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_6].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_6].h = ALTO_AVION_COMUN;

    //Septimo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_7].x = 0 + ANCHO_AVION_COMUN * 4;
    this->clipsAnimacion[LOOP_ETAPA_7].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_7].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_7].h = ALTO_AVION_COMUN;

    //Octavo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_8].x = 0;
    this->clipsAnimacion[LOOP_ETAPA_8].y = 0 + ALTO_AVION_COMUN * 2;
    this->clipsAnimacion[LOOP_ETAPA_8].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_8].h = ALTO_AVION_COMUN;

    //Noveno sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_9].x = 0 + ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_9].y = 0 + ALTO_AVION_COMUN * 2;
    this->clipsAnimacion[LOOP_ETAPA_9].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_9].h = ALTO_AVION_COMUN;

    //Octavo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_10].x = 0;
    this->clipsAnimacion[LOOP_ETAPA_10].y = 0 + ALTO_AVION_COMUN * 2;
    this->clipsAnimacion[LOOP_ETAPA_10].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_10].h = ALTO_AVION_COMUN;

    //Septimo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_11].x = 0 + ANCHO_AVION_COMUN * 4;
    this->clipsAnimacion[LOOP_ETAPA_11].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_11].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_11].h = ALTO_AVION_COMUN;

    //Sexto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_12].x = 0 + ANCHO_AVION_COMUN * 3;
    this->clipsAnimacion[LOOP_ETAPA_12].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_12].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_12].h = ALTO_AVION_COMUN;

    //Quinto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_13].x = 0 + ANCHO_AVION_COMUN * 2;
    this->clipsAnimacion[LOOP_ETAPA_13].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_13].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_13].h = ALTO_AVION_COMUN;

    //Cuarto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_14].x = 0 + ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_14].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_14].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_14].h = ALTO_AVION_COMUN;

    //Tercer sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_15].x = 0;
    this->clipsAnimacion[LOOP_ETAPA_15].y = 0 + ALTO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_15].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_15].h = ALTO_AVION_COMUN;

    //Segundo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_16].x = 0 + ANCHO_AVION_COMUN * 4;
    this->clipsAnimacion[LOOP_ETAPA_16].y = 0;
    this->clipsAnimacion[LOOP_ETAPA_16].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_16].h = ALTO_AVION_COMUN;

    //Primer sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_17].x = 0 + ANCHO_AVION_COMUN * 3;
    this->clipsAnimacion[LOOP_ETAPA_17].y = 0;
    this->clipsAnimacion[LOOP_ETAPA_17].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[LOOP_ETAPA_17].h = ALTO_AVION_COMUN;

    this->clipsAnimacion[DESCONECTADO].x = 0 + ANCHO_AVION_COMUN * 2;
    this->clipsAnimacion[DESCONECTADO].y = 0 + ALTO_AVION_COMUN * 2;
    this->clipsAnimacion[DESCONECTADO].w = ANCHO_AVION_COMUN;
    this->clipsAnimacion[DESCONECTADO].h = ALTO_AVION_COMUN;

}

int AvionVista::actualizar(string codigo){
    int sonido = CODIGO_SIN_SONIDO;
    pthread_mutex_lock(&mutexActualizar);
    this->posX = Decodificador::popFloat(codigo);
    this->posY = Decodificador::popFloat(codigo);
    int estadoAnimacionActual = Decodificador::popByte(codigo);
    if (estadoAnimacionActual >= OFFSET_ESTADO_DISPARO && estadoAnimacionActual < OFFSET_ESTADO_LOOP){
        sonido = CODIGO_SONIDO_DISPARO;
        estadoAnimacionActual = estadoAnimacionActual - OFFSET_ESTADO_DISPARO;
    } else if (estadoAnimacionActual >= OFFSET_ESTADO_LOOP && estadoAnimacionActual < OFFSET_ESTADO_EXPLOSION){
        sonido = CODIGO_SONIDO_LOOP;
        estadoAnimacionActual = estadoAnimacionActual - OFFSET_ESTADO_LOOP;
    }
    this->estadoAnimacion = estadoAnimacionActual;
    pthread_mutex_unlock(&mutexActualizar);

    return sonido;
}

void AvionVista::cargarImagen(SDL_Renderer* renderer, int color){
    if(!this->figura->loadFromFile(this->pathSprite, renderer, color)){
        this->figura->loadFromFile((string)AVION_POR_DEFECTO, renderer, color);
    }
}

void AvionVista::render(SDL_Renderer* renderer){
    pthread_mutex_lock(&mutexActualizar);
    figura->render((int)posX, (int)posY, renderer, &clipsAnimacion[estadoAnimacion]);
    pthread_mutex_unlock(&mutexActualizar);
}

void AvionVista::cerrar(){
    this->figura->free();
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

//
