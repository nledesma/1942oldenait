#ifndef MENUPOREQUIPOS_H
#define MENUPOREQUIPOS_H

#include "menu.hpp"
#include "../Boton/botonSiguiente.hpp"
#include "../listaDeSeleccion.hpp"
using namespace std;

class MenuPorEquipos: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        ListaDeSeleccion* lista;
    public:
        MenuPorEquipos(Ventana* ventana);
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        ListaDeSeleccion* &getListaDeSeleccion();
        void cerrar();

};

#endif
