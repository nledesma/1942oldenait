#include "menuConexionManual.hpp"

MenuConexionManual::MenuConexionManual(Ventana * ventana) : MenuInput(ventana){
    titulo->cargarFuente("INGRESE IP");
}

void MenuConexionManual::setMenuConexiones(Menu * menu) {
    anterior = menu;
}

void MenuConexionManual::setMenuPuerto(Menu * menu) {
    siguiente = menu;
}

void MenuConexionManual::accionAnterior() {}

void MenuConexionManual::accionSiguiente() {
    cout << "acá se debería setear la IP." << endl;
}

string MenuConexionManual::getIP() {
    return input->getTexto();
}
