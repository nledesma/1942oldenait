#include "manejador1942.hpp"

Manejador1942::Manejador1942(Ventana * ventana, Cliente * cliente) : ManejadorDeMenues(ventana){
    this->cliente = cliente;

    /* Creación de menúes */
    menuPrincipal = new MenuPrincipal(ventana);
    menuConexiones = new MenuConexiones(ventana, cliente);
    menuIp = new MenuConexionManual(ventana);
    menuPuerto = new MenuConexionPuerto(ventana);
    menuDatosDeUsuario = new MenuDatosDeUsuario(ventana, cliente);
    menuPorEquipos = new MenuPorEquipos(ventana);

    /* Relación entre menúes */
    menuPrincipal->setMenuDatosUsuario(menuDatosDeUsuario);

    menuConexiones->setMenuConexionManual(menuIp);
    menuConexiones->setMenuDatosUsuario(menuDatosDeUsuario);
    menuConexiones->setMenuPorEquipos(menuPorEquipos);

    menuIp->setMenuConexiones(menuConexiones);
    menuIp->setMenuPuerto(menuPuerto);

    menuPuerto->setMenuEquipos(menuPorEquipos);
    menuPuerto->setMenuIP(menuIp);

    menuDatosDeUsuario->setMenuConexiones(menuConexiones);
    menuDatosDeUsuario->setMenuPrincipal(menuPrincipal);

    // Por ahora si se sale del de equipos se va al principal.
    menuPorEquipos->setAnterior(menuPrincipal);

    actual = menuPrincipal;
}

Manejador1942::~Manejador1942() {

}

void Manejador1942::manejarEvento(int evento){
    if (evento == JUGAR) {
        cliente->ejecutar();
        // cout << "Acá debería ejecutarse el cliente. " << endl;
    } else {
        ManejadorDeMenues::manejarEvento(evento);
    }
}
