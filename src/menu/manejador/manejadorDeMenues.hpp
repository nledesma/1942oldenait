#ifndef MANEJADOR_MENU_HPP
#define MANEJADOR_MENU_HPP

#include "../Menu/menu.hpp"

class ManejadorDeMenues {
private:
    Ventana * ventana;
    bool dibujar;
protected:
    Menu * actual;
public:
    ManejadorDeMenues (Ventana * ventana);
    virtual ~ManejadorDeMenues ();
    void menuAnterior();
    void menuSiguiente();
    void renderLoop();
    void finalizarRender();
    void manejarEvento(int evento);
};

#endif
