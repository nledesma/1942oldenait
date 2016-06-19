#ifndef MENUCONEXIONMANUAL_H
#define MENUCONEXIONMANUAL_H

#include "../Boton/boton.hpp"
#include "menu.hpp"
using namespace std;

class MenuConexionManual: public Menu{
    private:
        Boton* botonSiguiente;
        Boton* botonAtras;
        Texto* textoIP;
    public:
        MenuConexionManual();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        Boton* getBotonSiguiente();
        Boton * getBotonAtras();
        void cerrar();
};

#endif
