#ifndef MENU_INTERMEDIO_HPP
#define MENU_INTERMEDIO_HPP

#include "../menu.hpp"
#include "../../Boton/boton.hpp"

class MenuIntermedio : public Menu {
protected:
    Boton* botonSiguiente;
    Boton* botonAtras;
public:
    MenuIntermedio (Ventana * ventana);
    void cargarBotones();
    virtual int manejarEvento(SDL_Event * e);
    virtual void render();
};

#endif
