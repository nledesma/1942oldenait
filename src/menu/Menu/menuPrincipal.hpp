#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "../Boton/boton.hpp"
#include "menu.hpp"
using namespace std;

class MenuPrincipal: public Menu{
    private:
        Boton* botonJugar;
        Boton* botonSalir;
        Figura* figuraLetras;
    public:
        MenuPrincipal();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        Boton* getBotonJugar();
        Boton* getBotonSalir();
        void cerrar();
};

#endif
