#ifndef MENU_DATOS_DE_USUARIO_HPP
#define MENU_DATOS_DE_USUARIO_HPP

#include "menuInput.hpp"
using namespace std;

class MenuDatosDeUsuario: public MenuInput {
    public:
        MenuDatosDeUsuario(Ventana * ventana);
        void setMenuPrincipal(Menu * m);
        void setMenuConexiones(Menu * m);
        void accionAnterior();
        void accionSiguiente();
};

#endif
