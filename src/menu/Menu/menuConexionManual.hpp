#ifndef MENUCONEXIONMANUAL_H
#define MENUCONEXIONMANUAL_H

#include "../Boton/botonSiguiente.hpp"
#include "menu.hpp"
using namespace std;

class MenuConexionManual: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        Texto* textoIP;
    public:
        MenuConexionManual();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        void cerrar();
};

#endif
