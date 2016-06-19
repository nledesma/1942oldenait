#ifndef MENU_LISTA_HPP
#define MENU_LISTA_HPP

#include "../menuIntermedio.hpp"
#include "../../../listaDeSeleccion.hpp"

#define ALTURA_TITULO 100

class MenuLista : public MenuIntermedio {
protected:
    Texto * titulo;
    ListaDeSeleccion* lista;
public:
    MenuLista (Ventana * ventana);
    // virtual ~MenuLista ();
    virtual void render();
    virtual int manejarEvento(SDL_Event * e);
};

#endif
