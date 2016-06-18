#include "menuLista.hpp"

MenuLista::MenuLista (Ventana * ventana) : MenuIntermedio (ventana) {
    titulo = new Texto(35, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    lista = new ListaDeSeleccion(ventana, 100, 150);
}

void MenuLista::render() {
    lista->renderizar();
    titulo->renderCentrado(ALTURA_TITULO);
    MenuIntermedio::render();
}

int MenuLista::manejarEvento(SDL_Event * e) {
    lista->manejarEvento(e);
    return MenuIntermedio::manejarEvento(e);
}
