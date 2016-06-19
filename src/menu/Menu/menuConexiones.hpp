#ifndef MENUCONEXIONES_H
#define MENUCONEXIONES_H

#include "menu.hpp"
#include "../Boton/boton.hpp"
#include "../listaDeSeleccion.hpp"
using namespace std;

class MenuConexiones: public Menu{
    private:
        Boton* botonSiguiente;
        Boton* botonAtras;
        ListaDeSeleccion* lista;
    public:
        MenuConexiones(Ventana* ventana);
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        Boton* getBotonSiguiente();
        Boton * getBotonAtras();
        ListaDeSeleccion* &getListaDeSeleccion();
        void cerrar();

};

#endif
