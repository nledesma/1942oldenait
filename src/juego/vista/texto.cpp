#include "texto.hpp"

Texto::Texto(int tamanioFuente, SDL_Color color, string fuente, Ventana * ventana) {
    this->texto = new Figura();
    this->fuente = TTF_OpenFont(fuente.c_str(), tamanioFuente);
    this->color = color;
    this->ventana = ventana;
}

Texto::~Texto() {
    // TTF_CloseFont(this->fuente);
    this->texto->free();
    this->fuente = NULL;
}

void Texto::cargarFuente(string textoString) {
    // pthread_mutex_lock(&mutexTexto);
    this->texto->loadFromRenderedText(textoString, this->color, this->fuente, ventana->getVentanaRenderer());
    // pthread_mutex_unlock(&mutexTexto);
}

void Texto::renderizar(int x , int y) {
    // pthread_mutex_lock(&mutexTexto);
    this->texto->render(x, y, this->ventana->getVentanaRenderer());
    // pthread_mutex_unlock(&mutexTexto);
}

void Texto::renderDerecho(int x, int y){
    int posX = x - texto->getWidth();
    texto->render(posX, y, this->ventana->getVentanaRenderer());
}

void Texto::renderCentrado(int y){
    int posX = ventana->getAncho()/2 - texto->getWidth()/2;
    texto->render(posX, y, this->ventana->getVentanaRenderer());
}

Figura* Texto::getFigura() {
    return this->texto;
}

TTF_Font* Texto::getFuente() {
    return this->fuente;
}
