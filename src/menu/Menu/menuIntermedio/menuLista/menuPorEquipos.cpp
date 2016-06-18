#include "menuPorEquipos.hpp"

MenuPorEquipos::MenuPorEquipos(Ventana* ventana, Cliente * cliente) : MenuLista(ventana){
    this->cliente = cliente;
    titulo->cargarFuente("SELECCIONE UN EQUIPO");
    siguiente = this;
    agregarOpciones();
}

void MenuPorEquipos::agregarOpciones() {
    lista->agregarOpcion("EQUIPO 1");
    lista->agregarOpcion("EQUIPO 2");
}

void MenuPorEquipos::accionAnterior() {}

void MenuPorEquipos::accionSiguiente() {}

void MenuPorEquipos::setAnterior(Menu * menu) {
    anterior = menu;
}

int MenuPorEquipos::manejarEvento(SDL_Event * e) {
    if (esTecla(e,SDLK_RETURN) || botonSiguiente->manejarEvento(e) == BOTON_APRETADO) {
        // TODO ver si falla este envío qué pasa.
        cliente->enviarEvento(lista->getNroBotonSeleccionado());
        return JUGAR;
    }
    return MenuLista::manejarEvento(e);
}
