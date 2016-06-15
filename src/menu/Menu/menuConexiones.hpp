#ifndef MENUCONEXIONES_H
#define MENUCONEXIONES_H

#include "menu.hpp"
#include "../Boton/botonSiguiente.hpp"
#include "../Boton/botonAtras.hpp"
#include "../listaDeSeleccion.hpp"
using namespace std;

class MenuConexiones: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        BotonAtras* botonAtras;
        ListaDeSeleccion* lista;
    public:
        MenuConexiones(Ventana* ventana);
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        BotonAtras * getBotonAtras();
        ListaDeSeleccion* &getListaDeSeleccion();
        void cerrar();

};

#endif
