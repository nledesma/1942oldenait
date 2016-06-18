#ifndef MANEJADOR_1942_HPP
#define MANEJADOR_1942_HPP

#include "manejadorDeMenues.hpp"
#include "../Menu/menuPrincipal.hpp"
#include "../Menu/menuIntermedio/menuLista/menuConexiones.hpp"
#include "../Menu/menuIntermedio/menuLista/menuPorEquipos.hpp"
#include "../Menu/menuIntermedio/menuInput/menuConexionManual.hpp"
#include "../Menu/menuIntermedio/menuInput/menuConexionPuerto.hpp"
#include "../Menu/menuIntermedio/menuInput/menuDatosDeUsuario.hpp"

class Manejador1942 : public ManejadorDeMenues {
private:
    MenuPrincipal * menuPrincipal;
    MenuConexiones * menuConexiones;
    MenuPorEquipos * menuPorEquipos;
    MenuConexionManual * menuIp;
    MenuConexionPuerto * menuPuerto;
    MenuDatosDeUsuario * menuDatosDeUsuario;
public:
    Manejador1942 (Ventana * ventana);
    virtual ~Manejador1942 ();
};

#endif