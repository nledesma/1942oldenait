#include "menuDatosDeUsuario.hpp"

MenuDatosDeUsuario::MenuDatosDeUsuario(Ventana * ventana) : MenuInput(ventana) {
    titulo->cargarFuente("Ingrese un Alias");
}

void MenuDatosDeUsuario::setMenuPrincipal(Menu * m) {
    anterior = m;
}

void MenuDatosDeUsuario::setMenuConexiones(Menu * m) {
    siguiente = m;
}

void MenuDatosDeUsuario::accionAnterior() {}

void MenuDatosDeUsuario::accionSiguiente() {
    cout << "Acá se debería setear el alias del cliente." << endl;
}
