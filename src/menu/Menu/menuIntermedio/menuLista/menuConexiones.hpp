#ifndef MENUCONEXIONES_H
#define MENUCONEXIONES_H

#include "menuLista.hpp"
#include "../../../../net/cliente/clienteParser.hpp"
using namespace std;

class MenuConexiones: public MenuLista {
    private:
        Menu * menuPorEquipos;
        Menu * menuConexionManual;
        // Texto * titulo;
    public:
        MenuConexiones(Ventana* ventana);
        ~MenuConexiones();
        void agregarOpciones();
        void setMenuConexionManual(Menu * m);
        void setMenuDatosUsuario(Menu * m);
        void setMenuPorEquipos(Menu * m);
        void accionAnterior();
        void accionSiguiente();

};

#endif
