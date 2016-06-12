#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "../Boton/botonJugar.hpp"
#include "../Boton/botonSalir.hpp"
#include "menu.hpp"
using namespace std;

class MenuPrincipal: public Menu{
    private:
        BotonJugar* botonJugar;
        BotonSalir* botonSalir;
        Texto* texto;
    public:
        MenuPrincipal();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonJugar* getBotonJugar();
        BotonSalir* getBotonSalir();
        void cerrar();
};

#endif
