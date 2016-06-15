#ifndef MENUDATOSDEUSUARIO_H
#define MENUDATOSDEUSUARIO_H

#include "menu.hpp"
#include "../Boton/botonSiguiente.hpp"
#include "../Boton/botonAtras.hpp"
using namespace std;

class MenuDatosDeUsuario: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        BotonAtras* botonAtras;
        Texto* texto;
    public:
        MenuDatosDeUsuario();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        BotonAtras * getBotonAtras();
        void cerrar();

};

#endif
