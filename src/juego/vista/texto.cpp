#include "texto.hpp"

Texto::Texto(int tamanioFuente, SDL_Color color, Ventana * ventana) {
    this->texto = new Figura();
    this->fuente = TTF_OpenFont(STAR_WARS_FONT, tamanioFuente);
    this->color = color;
    this->ventana = ventana;
}

Texto::~Texto() {
    TTF_CloseFont(this->fuente);
    this->texto->free();
    this->fuente = NULL;
}

void Texto::cargarFuente(string textoString) {
    this->texto->loadFromRenderedText(textoString, this->color, this->fuente, ventana->getVentanaRenderer());
}

void Texto::renderizar(int x , int y) {
    this->texto->render(x, y, this->ventana->getVentanaRenderer());
}

Figura* Texto::getFigura() {
    return this->texto;
}

TTF_Font* Texto::getFuente() {
    return this->fuente;
}
