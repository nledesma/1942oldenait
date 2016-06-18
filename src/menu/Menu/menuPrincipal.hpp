#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "../Boton/botonJugar.hpp"
#include "../Boton/botonSalir.hpp"
#include "menu.hpp"
using namespace std;

class MenuPrincipal: public Menu {
    private:
        BotonJugar* botonJugar;
        BotonSalir* botonSalir;
        Figura* titulo;
    public:
        MenuPrincipal(Ventana * ventana);
        void cerrar();
        void cargarFiguras();
        void setMenuDatosUsuario(Menu * m);
        int manejarEvento(SDL_Event * e);
        void accionAnterior();
        void accionSiguiente();
        void render();
};

#endif
