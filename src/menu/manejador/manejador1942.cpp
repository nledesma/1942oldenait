#include "manejador1942.hpp"

Manejador1942::Manejador1942(Ventana * ventana) : ManejadorDeMenues(ventana){
    /* Creación de menúes */
    menuPrincipal = new MenuPrincipal(ventana);
    menuConexiones = new MenuConexiones(ventana);
    menuIp = new MenuConexionManual(ventana);
    menuPuerto = new MenuConexionPuerto(ventana);
    menuDatosDeUsuario = new MenuDatosDeUsuario(ventana);
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
