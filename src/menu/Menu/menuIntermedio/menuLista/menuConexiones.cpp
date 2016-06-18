#include "menuConexiones.hpp"

MenuConexiones::MenuConexiones(Ventana* ventana) : MenuLista(ventana){
    titulo->cargarFuente("CONEXIONES");
    agregarOpciones();
}

MenuConexiones::~MenuConexiones() {
    //TODO Liberar cosas.
}

void MenuConexiones::agregarOpciones() {
    list<Conexion> conexionesGuardadas = ClienteParser::levantarConexiones();
    list<Conexion>::iterator it;
    for(it = conexionesGuardadas.begin(); it != conexionesGuardadas.end(); it ++){
        string conexion = it->nombre + ". ip: " + it->ip + ". puerto: " + to_string(it->puerto);
        lista->agregarOpcion(conexion);
    }
    lista->agregarOpcion("conexion manual");
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
