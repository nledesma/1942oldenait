#include "avionSecundarioVista.hpp"

AvionSecundarioVista::AvionSecundarioVista(float posX, float posY){
    this->iniciarAvion(posX, posY);
}

AvionSecundarioVista::AvionSecundarioVista(string infoAvion){
    float posX = Decodificador::popFloat(infoAvion);
    float posY = Decodificador::popFloat(infoAvion);
    this->iniciarAvion(posX, posY);
}

AvionSecundarioVista::~AvionSecundarioVista() { }

void AvionSecundarioVista::iniciarAvion(float posX, float posY){
    this->posX = posX;
    this->posY = posY;
    this->estadoAnimacion = ESTADO_AVION_SECUNDARIO_NORMAL;
    this->pathSprite = SPRITE_AVION_SECUNDARIO;
    this->figura = new Figura();
    int ancho = ANCHO_AVION_SECUNDARIO;
    int alto = ALTO_AVION_SECUNDARIO;

    //cout << "posX despues de decodificar en iniciarAvion: " << this->posX << endl;
    //cout << "posY despues de decodificar en iniciarAvion: " << this->posY << endl;

    //Avión en estado normal
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_NORMAL].x = 0;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_NORMAL].y = 0;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_NORMAL].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_NORMAL].h = alto;

    //Avión moviéndose a la izquierda
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_GIRANDO_IZQUIERDA].x = 0 + ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_GIRANDO_IZQUIERDA].y = 0;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_GIRANDO_IZQUIERDA].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_GIRANDO_IZQUIERDA].h = alto;

    //Avión moviéndose a la derecha
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_GIRANDO_DERECHA].x = 0 + ancho * 2;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_GIRANDO_DERECHA].y = 0;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_GIRANDO_DERECHA].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_GIRANDO_DERECHA].h = alto;

    //Avión desconectado
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_DESCONECTADO].x = 0 + ancho * 3;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_DESCONECTADO].y = 0;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_DESCONECTADO].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_DESCONECTADO].h = alto;

    //Explotar
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_1].x = 0;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_1].y = 0 + alto;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_1].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_1].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_2].x = 0 + ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_2].y = 0 + alto;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_2].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_2].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_3].x = 0 + ancho * 2;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_3].y = 0 + alto;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_3].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_3].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_4].x = 0 + ancho * 3;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_4].y = 0 + alto;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_4].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_4].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_5].x = 0 + ancho * 4;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_5].y = 0 + alto;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_5].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_5].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_6].x = 0;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_6].y = 0 + alto * 2;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_6].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_6].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_7].x = 0 + ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_7].y = 0 + alto * 2;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_7].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_7].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_8].x = 0 + ancho * 2;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_8].y = 0 + alto * 2;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_8].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_8].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_9].x = 0 + ancho * 3;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_9].y = 0 + alto * 2;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_9].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_9].h = alto;

    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_10].x = 0 + ancho * 4;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_10].y = 0 + alto * 2;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_10].w = ancho;
    this->clipsAnimacion[ESTADO_AVION_SECUNDARIO_EXPLOSION_10].h = alto;

}

int AvionSecundarioVista::actualizar(string codigo){
    int sonido = CODIGO_SIN_SONIDO;
    pthread_mutex_lock(&mutexActualizarAvionesSecundarios);
    this->posX = Decodificador::popFloat(codigo);
    cout << "posX despues de decodificar en avionSecundarioVista: " << this->posX << endl;
    this->posY = Decodificador::popFloat(codigo);
    cout << "posY despues de decodificar en avionSecundarioVista: " << this->posY << endl;
    int estadoAnimacionActual = Decodificador::popInt(codigo);
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
    pthread_mutex_unlock(&mutexActualizarAvionesSecundarios);

    return sonido;
}

void AvionSecundarioVista::cargarImagen(SDL_Renderer* renderer, int color){
    if(!this->figura->loadFromFile(this->pathSprite, renderer, color)){
        this->figura->loadFromFile((string)SPRITE_AVION_SECUNDARIO, renderer, color);
    }
}

void AvionSecundarioVista::render(SDL_Renderer* renderer){
    pthread_mutex_lock(&mutexActualizarAvionesSecundarios);
    if (this->estadoAnimacion != ESTADO_AVION_SECUNDARIO_DESTRUIDO) {
        figura->render((int) posX, (int) posY, renderer, &clipsAnimacion[estadoAnimacion]);
    }
    pthread_mutex_unlock(&mutexActualizarAvionesSecundarios);
}

void AvionSecundarioVista::cerrar(){
    this->figura->free();
}

float AvionSecundarioVista::getPosX(){
    return this->posX;
}

float AvionSecundarioVista::getPosY(){
    return this->posY;
}

int AvionSecundarioVista::getAncho() {
    return this->figura->getWidth();
}

int AvionSecundarioVista::getAlto() {
    return this->figura->getHeight();
}

Figura* AvionSecundarioVista::getFigura(){
    return this->figura;
}

int AvionSecundarioVista::getEstadoAnimacion(){
    return this->estadoAnimacion;
}

void AvionSecundarioVista::setPosX(float posX){
    this->posX = posX;
}

void AvionSecundarioVista::setPosY(float posY){
    this->posY = posY;
}

void AvionSecundarioVista::setFigura(Figura * figura){
    this->figura = figura;
}

void AvionSecundarioVista::setEstadoAnimacion(int estadoAnimacion){
    this->estadoAnimacion = estadoAnimacion;
}

void AvionSecundarioVista::cargarAvionSecundario(SDL_Renderer* renderer){
    this->figura->loadFromFile(this->pathSprite,renderer);
}
