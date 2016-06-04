#include "texto.hpp"
Texto::Texto(int tamanioFuente, SDL_Color color){
    this->texto = new Figura();
    this->fuente = TTF_OpenFont("../../resources/fonts/STARWARS.ttf",tamanioFuente);
    this->color = color;

}

void Texto::cargarFuente(string textoString, Ventana* ventana){
    cout << this->fuente << endl;
    this->texto->loadFromRenderedText(textoString, this->color, this->fuente, ventana->getVentanaRenderer());
}

void Texto::renderizar(int x , int y, SDL_Renderer* renderer){
    this->texto->render(x, y, renderer);
}

Figura* Texto::getFigura(){
    return this->texto;
}

TTF_Font* Texto::getFuente(){
    return this->fuente;
}

Texto::~Texto(){
    this->texto->free();
    TTF_CloseFont(this->fuente);
    this->fuente = NULL;
}
