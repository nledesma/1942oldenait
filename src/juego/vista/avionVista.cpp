#include "avionVista.hpp"

AvionVista::AvionVista(float posX, float posY, string pathSprite, int estadoPowerUP){
    this->iniciarAvion(posX, posY, pathSprite, estadoPowerUP);
    //this->vidas = 0;
}

AvionVista::AvionVista(string infoAvion){
    float posX = Decodificador::popFloat(infoAvion);
    float posY = Decodificador::popFloat(infoAvion);
    this->iniciarAvion(posX, posY, infoAvion, estadoPowerUP );
    this->vidas = -1;
}

AvionVista::~AvionVista() { }

void AvionVista::iniciarAvion(float posX, float posY, string pathSprite, int estadoPowerUP){
    this->posX = posX;
    this->posY = posY;
    this->estadoAnimacion = ESTADO_NORMAL;
    this->pathSprite = pathSprite;
    this->figura = new Figura();
    this->estadoPowerUP = estadoPowerUP;
    int ancho = ANCHO_AVION_COMUN;
    int alto = ALTO_AVION_COMUN;

    //Avión en estado normal
    this->clipsAnimacion[ESTADO_NORMAL].x = 0;
    this->clipsAnimacion[ESTADO_NORMAL].y = 0;
    this->clipsAnimacion[ESTADO_NORMAL].w = ancho;
    this->clipsAnimacion[ESTADO_NORMAL].h = alto;

    //Avión moviéndose a la izquierda
    this->clipsAnimacion[GIRANDO_IZQUIERDA].x = 0 + ancho;
    this->clipsAnimacion[GIRANDO_IZQUIERDA].y = 0;
    this->clipsAnimacion[GIRANDO_IZQUIERDA].w = ancho;
    this->clipsAnimacion[GIRANDO_IZQUIERDA].h = alto;

    //Avión moviéndose a la derecha
    this->clipsAnimacion[GIRANDO_DERECHA].x = 0 + ancho * 2;
    this->clipsAnimacion[GIRANDO_DERECHA].y = 0;
    this->clipsAnimacion[GIRANDO_DERECHA].w = ancho;
    this->clipsAnimacion[GIRANDO_DERECHA].h = alto;

    //Primer sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_1].x = 0 + ancho * 3;
    this->clipsAnimacion[LOOP_ETAPA_1].y = 0;
    this->clipsAnimacion[LOOP_ETAPA_1].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_1].h = alto;

    //Segundo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_2].x = 0 + ancho * 4;
    this->clipsAnimacion[LOOP_ETAPA_2].y = 0;
    this->clipsAnimacion[LOOP_ETAPA_2].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_2].h = alto;

    //Tercer sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_3].x = 0;
    this->clipsAnimacion[LOOP_ETAPA_3].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_3].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_3].h = alto;

    //Cuarto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_4].x = 0 + ancho;
    this->clipsAnimacion[LOOP_ETAPA_4].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_4].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_4].h = alto;

    //Quinto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_5].x = 0 + ancho * 2;
    this->clipsAnimacion[LOOP_ETAPA_5].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_5].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_5].h = alto;

    //Sexto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_6].x = 0 + ancho * 3;
    this->clipsAnimacion[LOOP_ETAPA_6].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_6].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_6].h = alto;

    //Septimo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_7].x = 0 + ancho * 4;
    this->clipsAnimacion[LOOP_ETAPA_7].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_7].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_7].h = alto;

    //Octavo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_8].x = 0;
    this->clipsAnimacion[LOOP_ETAPA_8].y = 0 + alto * 2;
    this->clipsAnimacion[LOOP_ETAPA_8].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_8].h = alto;

    //Noveno sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_9].x = 0 + ancho;
    this->clipsAnimacion[LOOP_ETAPA_9].y = 0 + alto * 2;
    this->clipsAnimacion[LOOP_ETAPA_9].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_9].h = alto;

    //Octavo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_10].x = 0;
    this->clipsAnimacion[LOOP_ETAPA_10].y = 0 + alto * 2;
    this->clipsAnimacion[LOOP_ETAPA_10].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_10].h = alto;

    //Septimo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_11].x = 0 + ancho * 4;
    this->clipsAnimacion[LOOP_ETAPA_11].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_11].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_11].h = alto;

    //Sexto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_12].x = 0 + ancho * 3;
    this->clipsAnimacion[LOOP_ETAPA_12].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_12].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_12].h = alto;

    //Quinto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_13].x = 0 + ancho * 2;
    this->clipsAnimacion[LOOP_ETAPA_13].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_13].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_13].h = alto;

    //Cuarto sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_14].x = 0 + ancho;
    this->clipsAnimacion[LOOP_ETAPA_14].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_14].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_14].h = alto;

    //Tercer sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_15].x = 0;
    this->clipsAnimacion[LOOP_ETAPA_15].y = 0 + alto;
    this->clipsAnimacion[LOOP_ETAPA_15].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_15].h = alto;

    //Segundo sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_16].x = 0 + ancho * 4;
    this->clipsAnimacion[LOOP_ETAPA_16].y = 0;
    this->clipsAnimacion[LOOP_ETAPA_16].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_16].h = alto;

    //Primer sprite vuelta
    this->clipsAnimacion[LOOP_ETAPA_17].x = 0 + ancho * 3;
    this->clipsAnimacion[LOOP_ETAPA_17].y = 0;
    this->clipsAnimacion[LOOP_ETAPA_17].w = ancho;
    this->clipsAnimacion[LOOP_ETAPA_17].h = alto;

    this->clipsAnimacion[DESCONECTADO].x = 0 + ancho * 2;
    this->clipsAnimacion[DESCONECTADO].y = 0 + alto * 2;
    this->clipsAnimacion[DESCONECTADO].w = ancho;
    this->clipsAnimacion[DESCONECTADO].h = alto;

    //Explotar
    this->clipsAnimacion[EXPLOSION_ETAPA_1].x = 0;
    this->clipsAnimacion[EXPLOSION_ETAPA_1].y = 0 + alto * 3;
    this->clipsAnimacion[EXPLOSION_ETAPA_1].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_1].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_2].x = 0 + ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_2].y = 0 + alto * 3;
    this->clipsAnimacion[EXPLOSION_ETAPA_2].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_2].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_3].x = 0 + ancho * 2;
    this->clipsAnimacion[EXPLOSION_ETAPA_3].y = 0 + alto * 3;
    this->clipsAnimacion[EXPLOSION_ETAPA_3].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_3].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_4].x = 0 + ancho * 3;
    this->clipsAnimacion[EXPLOSION_ETAPA_4].y = 0 + alto * 3;
    this->clipsAnimacion[EXPLOSION_ETAPA_4].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_4].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_5].x = 0 + ancho * 4;
    this->clipsAnimacion[EXPLOSION_ETAPA_5].y = 0 + alto * 3;
    this->clipsAnimacion[EXPLOSION_ETAPA_5].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_5].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_6].x = 0;
    this->clipsAnimacion[EXPLOSION_ETAPA_6].y = 0 + alto * 4;
    this->clipsAnimacion[EXPLOSION_ETAPA_6].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_6].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_7].x = 0 + ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_7].y = 0 + alto * 4;
    this->clipsAnimacion[EXPLOSION_ETAPA_7].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_7].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_8].x = 0 + ancho * 2;
    this->clipsAnimacion[EXPLOSION_ETAPA_8].y = 0 + alto * 4;
    this->clipsAnimacion[EXPLOSION_ETAPA_8].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_8].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_9].x = 0 + ancho * 3;
    this->clipsAnimacion[EXPLOSION_ETAPA_9].y = 0 + alto * 4;
    this->clipsAnimacion[EXPLOSION_ETAPA_9].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_9].h = alto;

    this->clipsAnimacion[EXPLOSION_ETAPA_10].x = 0 + ancho * 4;
    this->clipsAnimacion[EXPLOSION_ETAPA_10].y = 0 + alto * 4;
    this->clipsAnimacion[EXPLOSION_ETAPA_10].w = ancho;
    this->clipsAnimacion[EXPLOSION_ETAPA_10].h = alto;

    this->clipsAnimacion[ESTACIONADO].x = 0 + ancho * 5;
    this->clipsAnimacion[ESTACIONADO].y = 0 + alto * 4;
    this->clipsAnimacion[ESTACIONADO].w = ancho;
    this->clipsAnimacion[ESTACIONADO].h = alto;
}

int AvionVista::actualizar(string codigo){
    int sonido = CODIGO_SIN_SONIDO;
    pthread_mutex_lock(&mutexActualizar);
    this->posX = Decodificador::popFloat(codigo);
    this->posY = Decodificador::popFloat(codigo);
    int estadoPowerUPActual = Decodificador::popInt(codigo);
    this->estadoPowerUP = estadoPowerUPActual;
    int estadoAnimacionActual = Decodificador::popInt(codigo);
    this->vidas = Decodificador::popInt(codigo);
    if (estadoAnimacionActual >= OFFSET_ESTADO_DISPARO && estadoAnimacionActual < OFFSET_ESTADO_LOOP){
        sonido = CODIGO_SONIDO_DISPARO;
        estadoAnimacionActual = estadoAnimacionActual - OFFSET_ESTADO_DISPARO;
    } else if (estadoAnimacionActual >= OFFSET_ESTADO_LOOP && estadoAnimacionActual < OFFSET_ESTADO_EXPLOSION){
        sonido = CODIGO_SONIDO_LOOP;
        estadoAnimacionActual = estadoAnimacionActual - OFFSET_ESTADO_LOOP;
    } else if (estadoAnimacionActual >= OFFSET_ESTADO_EXPLOSION) {
        sonido = CODIGO_SONIDO_EXPLOSION;
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
    if (this->estadoAnimacion != ESTADO_AVION_DESTRUIDO) {
        if (this->estadoAnimacion != INTERMITENCIA) {
            figura->render((int) posX, (int) posY, renderer, &clipsAnimacion[estadoAnimacion]);
        } else {
            figura->render((int) posX, (int) posY, renderer, &clipsAnimacion[DESCONECTADO]);
        }
    }
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

int AvionVista::getVidas(){
    return this->vidas;
}

int AvionVista::getEstadoPowerUp(){
    return this->estadoPowerUP;
}
