#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "../Boton/boton.hpp"
#include "menu.hpp"
using namespace std;

class MenuPrincipal: public Menu {
    private:
        Boton* botonJugar;
        Boton* botonSalir;
        Figura* titulo;
    public:
        MenuPrincipal(Ventana * ventana);
        void cerrar();
        void cargarBotones();
        void setMenuDatosUsuario(Menu * m);
        int manejarEvento(SDL_Event * e);
        void accionAnterior();
        void accionSiguiente();
        void render();
};

#endif
