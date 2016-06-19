#include "menuConexionPuerto.hpp"

MenuConexionPuerto::MenuConexionPuerto(Ventana * ventana) : MenuInput(ventana){
    titulo->cargarFuente("INGRESE PUERTO");
}

void MenuConexionPuerto::setMenuIP(Menu * menu) {
    anterior = menu;
}

void MenuConexionPuerto::setMenuEquipos(Menu * menu) {
    siguiente = menu;
}

void MenuConexionPuerto::accionAnterior() {}

void MenuConexionPuerto::accionSiguiente() {
    cout << "acá se debería setear la IP." << input->getTexto() << endl;
    cout << "Luego de setear la IP se debería conectar." << endl;
}
