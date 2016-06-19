#ifndef MENUDATOSDEUSUARIO_H
#define MENUDATOSDEUSUARIO_H

#include "menu.hpp"
#include "../Boton/boton.hpp"
using namespace std;

class MenuDatosDeUsuario: public Menu{
    private:
        Boton* botonSiguiente;
        Boton* botonAtras;
        Texto* texto;
    public:
        MenuDatosDeUsuario();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        Boton* getBotonSiguiente();
        Boton * getBotonAtras();
        void cerrar();

};

#endif
