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
        bool cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonJugar* getBotonJugar();
        BotonSalir* getBotonSalir();
        TTF_Font* getTextoUsuario();
        Figura* getFiguraTextoUsuario();
        void cerrar();
};

#endif
