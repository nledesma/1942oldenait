#include "menuConexiones.hpp"

MenuConexiones::MenuConexiones(Ventana* ventana) : MenuLista(ventana){
    titulo->cargarFuente("CONEXIONES");
    agregarOpciones();
}

MenuConexiones::~MenuConexiones() {
    //TODO Liberar cosas.
}

void MenuConexiones::agregarOpciones() {
    cout << "Acá deberíamos levantar las conexiones y agregarlas." << endl;
}

void MenuConexiones::accionAnterior() {}

void MenuConexiones::accionSiguiente() {
    if (lista->getNroBotonSeleccionado() != lista->getCantidadOpciones() - 1) {
        cout << "Acá hay llamar al set adress del cliente." << endl;
        cout << "También debería entrar la parte de conexión." << endl;
        siguiente = menuPorEquipos;
    } else {
        siguiente = menuConexionManual;
    }
}

void MenuConexiones::setMenuConexionManual(Menu * m) {
    this->menuConexionManual = m;
}

void MenuConexiones::setMenuPorEquipos(Menu * m) {
    this->menuPorEquipos = m;
}

void MenuConexiones::setMenuDatosUsuario(Menu * m) {
    this->anterior = m;
}
