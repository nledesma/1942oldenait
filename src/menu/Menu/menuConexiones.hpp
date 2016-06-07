#ifndef MENUCONEXIONES_H
#define MENUCONEXIONES_H

#include "menu.hpp"
#include "../Boton/botonSiguiente.hpp"
#include "../listaDeSeleccion.hpp"
using namespace std;

class MenuConexiones: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        ListaDeSeleccion* lista;
    public:
        MenuConexiones(Ventana* ventana);
        bool cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        ListaDeSeleccion* &getListaDeSeleccion();
        void cerrar();

};

#endif
