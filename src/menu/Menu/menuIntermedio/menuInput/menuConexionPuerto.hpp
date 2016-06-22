#ifndef MENUCONEXIONPUERTO_H
#define MENUCONEXIONPUERTO_H

#include "menuInput.hpp"
#include "menuConexionManual.hpp"
using namespace std;

class MenuConexionPuerto: public MenuInput {
    private:
        Aviso * aviso;
        Cliente * cliente;
    public:
        MenuConexionPuerto(Ventana * ventana, Cliente * cliente);
        void setMenuIP(Menu * menu);
        void setMenuEquipos(Menu * menu);
        void accionAnterior();
        void accionSiguiente();
        int manejarEvento(SDL_Event * e);
        void render();
};

#endif
