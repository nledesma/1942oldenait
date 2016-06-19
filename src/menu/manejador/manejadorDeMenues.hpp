#ifndef MANEJADOR_MENU_HPP
#define MANEJADOR_MENU_HPP

#include "../Menu/menu.hpp"
#include "../../juego/vista/soundboard.hpp"

class ManejadorDeMenues {
private:
    Ventana * ventana;
    bool dibujar;
protected:
    Menu * actual;
    SoundBoard * soundBoard;
public:
    ManejadorDeMenues (Ventana * ventana, SoundBoard * soundBoard);
    virtual ~ManejadorDeMenues ();
    void menuAnterior();
    void menuSiguiente();
    void renderLoop();
    void finalizarRender();
    virtual void manejarEvento(int evento);
};

#endif
