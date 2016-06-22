#include "aviso.hpp"

Aviso::Aviso (Ventana * ventana) {
    texto = new TextoDinamico(15, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    this->ventana = ventana;
}

Aviso::~Aviso () {

}

void Aviso::avisar(string texto){
    cout << "Se llama a avisar!" << endl;
    visible = true;
    this->texto->cambiarTexto(texto);
    posX = (ventana->getAncho() - this->texto->getFigura()->getWidth())/2;
}

void Aviso::render() {
    if (visible) {
        texto->renderizar(posX, POSY);
    }
}

void Aviso::manejarEvento(SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState( &x, &y );
        if (x >= posX && x <= posX + texto->getFigura()->getWidth() &&
            y >= POSY && y <= POSY + texto->getFigura()->getHeight())
            visible = false;
    }
}
