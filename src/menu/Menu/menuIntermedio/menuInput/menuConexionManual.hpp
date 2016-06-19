#ifndef MENUCONEXIONMANUAL_H
#define MENUCONEXIONMANUAL_H

#include "../../../../juego/vista/textoDinamico.hpp"
#include "menuInput.hpp"
using namespace std;

class MenuConexionManual: public MenuInput {
    public:
        MenuConexionManual(Ventana * ventana);
        void setMenuPuerto(Menu * menu);
        void setMenuConexiones(Menu * menu);
        void accionAnterior();
        void accionSiguiente();
};

#endif
