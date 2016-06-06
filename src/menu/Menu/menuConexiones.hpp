#ifndef MENUCONEXIONES_H
#define MENUCONEXIONES_H

#include "menu.hpp"
#include "../Boton/botonSiguiente.hpp"
using namespace std;

class MenuConexiones: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
    public:
        MenuConexiones();
        bool cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        void cerrar();

};

#endif
