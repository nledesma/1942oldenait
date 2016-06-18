#include "menuPorEquipos.hpp"

MenuPorEquipos::MenuPorEquipos(Ventana* ventana) : MenuLista(ventana){
    titulo->cargarFuente("SELECCIONE UN EQUIPO");
    agregarOpciones();
}

void MenuPorEquipos::agregarOpciones() {
    lista->agregarOpcion("EQUIPO 1");
    lista->agregarOpcion("EQUIPO 2");
}

void MenuPorEquipos::accionAnterior() {
    cout << "Esto debería cancelar alguna cosa." << endl;
}

void MenuPorEquipos::accionSiguiente() {
    cout << "Esto debería mandar el mensaje del equipo y comenzar el juego." << endl;
}

void MenuPorEquipos::setAnterior(Menu * menu) {
    anterior = menu;
}
