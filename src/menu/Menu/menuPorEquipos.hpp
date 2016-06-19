#ifndef MENUPOREQUIPOS_H
#define MENUPOREQUIPOS_H

#include "menu.hpp"
#include "../Boton/boton.hpp"
#include "../listaDeSeleccion.hpp"
using namespace std;

class MenuPorEquipos: public Menu{
    private:
        Boton* botonSiguiente;
        ListaDeSeleccion* lista;
        Texto* texto;
    public:
        MenuPorEquipos(Ventana* ventana);
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        Boton* getBotonSiguiente();
        ListaDeSeleccion* &getListaDeSeleccion();
        void cerrar();

};

#endif
