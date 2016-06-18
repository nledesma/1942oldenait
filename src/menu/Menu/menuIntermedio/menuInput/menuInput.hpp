#ifndef MENU_INPUT_HPP
#define MENU_INPUT_HPP

#include "../menuIntermedio.hpp"
#include "../../../../juego/vista/textoDinamico.hpp"
#include "../../../../net/cliente/cliente.hpp"

#define ALTURA_TITULO 100

class MenuInput : public MenuIntermedio {
protected:
    Texto *titulo;
    TextoDinamico * input;
public:
    MenuInput (Ventana * ventana);
    // virtual ~MenuInput ();
    virtual void render();
    virtual int manejarEvento(SDL_Event * e);
};
#endif
