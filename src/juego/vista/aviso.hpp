#ifndef AVISO_HPP
#define AVISO_HPP

#include "textoDinamico.hpp"

#define POSY 600

class Aviso {
private:
    TextoDinamico * texto;
    Ventana * ventana;
    bool visible;
    int posX;
public:
    Aviso (Ventana * ventana);
    virtual ~Aviso ();
    void avisar(string texto);
    void render();
    void manejarEvento(SDL_Event *e);
};

#endif
