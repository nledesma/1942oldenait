#ifndef MENUCONEXIONPUERTO_H
#define MENUCONEXIONPUERTO_H

#include "menuInput.hpp"
using namespace std;

class MenuConexionPuerto: public MenuInput {
    public:
        MenuConexionPuerto(Ventana * ventana);
        void setMenuIP(Menu * menu);
        void setMenuEquipos(Menu * menu);
        void accionAnterior();
        void accionSiguiente();
};

#endif
