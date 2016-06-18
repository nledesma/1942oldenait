#ifndef MENU_INTERMEDIO_HPP
#define MENU_INTERMEDIO_HPP

#include "../menu.hpp"
#include "../../Boton/botonSiguiente.hpp"
#include "../../Boton/botonAtras.hpp"

class MenuIntermedio : public Menu {
protected:
    BotonSiguiente* botonSiguiente;
    BotonAtras* botonAtras;
public:
    MenuIntermedio (Ventana * ventana);
    void cargarBotones();
    virtual int manejarEvento(SDL_Event * e);
    virtual void render();
};

#endif
