#include "menuDatosDeUsuario.hpp"

MenuDatosDeUsuario::MenuDatosDeUsuario(Ventana * ventana, Cliente * cliente) : MenuInput(ventana) {
    this->cliente = cliente;
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
    cliente->setAlias(input->getTexto());
    cout << "se le dio al cliente el nombre" << cliente->getAlias() << endl;
}
