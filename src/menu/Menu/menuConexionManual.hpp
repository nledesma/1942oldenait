#ifndef MENUCONEXIONMANUAL_H
#define MENUCONEXIONMANUAL_H

#include "../Boton/botonSiguiente.hpp"
#include "../Boton/botonAtras.hpp"
#include "menu.hpp"
using namespace std;

class MenuConexionManual: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        BotonAtras* botonAtras;
        Texto* textoIP;
    public:
        MenuConexionManual();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        BotonAtras * getBotonAtras();
        void cerrar();
};

#endif
