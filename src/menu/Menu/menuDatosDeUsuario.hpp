#ifndef MENUDATOSDEUSUARIO_H
#define MENUDATOSDEUSUARIO_H

#include "menu.hpp"
#include "../Boton/botonSiguiente.hpp"
using namespace std;

class MenuDatosDeUsuario: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        Texto* texto;
    public:
        MenuDatosDeUsuario();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        void cerrar();

};

#endif
