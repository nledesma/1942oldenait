#include "menuInput.hpp"

MenuInput::MenuInput (Ventana * ventana) : MenuIntermedio(ventana) {
    titulo = new Texto(35, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    input = new TextoDinamico(25, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    input->cambiarTexto("");
}

void MenuInput::render() {
    titulo->renderCentrado(ALTURA_TITULO);
    input->renderCentrado(ALTURA_TITULO + 100);
    MenuIntermedio::render();
}

int MenuInput::manejarEvento(SDL_Event * e) {
    input->manejarEvento(*e);
    return MenuIntermedio::manejarEvento(e);
}
