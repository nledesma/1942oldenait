#ifndef MENUPOREQUIPOS_H
#define MENUPOREQUIPOS_H

#include "menuLista.hpp"
using namespace std;

class MenuPorEquipos: public MenuLista{
    private:
        void agregarOpciones();
    public:
        MenuPorEquipos(Ventana* ventana);
        void accionAnterior();
        void accionSiguiente();
        // Puede venir de más de un lugar.
        void setAnterior(Menu * menu);
};

#endif
