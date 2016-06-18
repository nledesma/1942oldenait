#ifndef MENUPOREQUIPOS_H
#define MENUPOREQUIPOS_H

#include "menuLista.hpp"
#include "../../../../net/cliente/cliente.hpp"
using namespace std;

class MenuPorEquipos: public MenuLista{
    private:
        void agregarOpciones();
        Cliente * cliente;
    public:
        MenuPorEquipos(Ventana* ventana, Cliente * cliente);
        void accionAnterior();
        void accionSiguiente();
        // Puede venir de más de un lugar.
        void setAnterior(Menu * menu);
        int manejarEvento(SDL_Event * e);
};

#endif
