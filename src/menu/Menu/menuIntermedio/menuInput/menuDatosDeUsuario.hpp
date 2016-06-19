#ifndef MENU_DATOS_DE_USUARIO_HPP
#define MENU_DATOS_DE_USUARIO_HPP

#include "menuInput.hpp"
#include "../../../../net/cliente/cliente.hpp"
using namespace std;

class MenuDatosDeUsuario: public MenuInput {
    private:
        Cliente * cliente;
    public:
        MenuDatosDeUsuario(Ventana * ventana, Cliente * cliente);
        void setMenuPrincipal(Menu * m);
        void setMenuConexiones(Menu * m);
        void accionAnterior();
        void accionSiguiente();
};

#endif
