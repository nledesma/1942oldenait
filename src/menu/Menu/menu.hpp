#ifndef MENU_H
#define MENU_H

#include "../Boton/botonJugar.hpp"
#include "../Boton/botonSalir.hpp"
#include "../../juego/vista/ventana.hpp"
#include "../../juego/vista/texto.hpp"
#include <list>
using namespace std;

#define ANTERIOR 0
#define SIGUIENTE 1
#define SALIR 2
#define NADA 3

class Menu {
    private:
        TTF_Font *gFont;
    protected:
        Ventana * ventana;
        Figura* fondo;
        Menu * siguiente;
        Menu * anterior;
        virtual void cargarBotones() = 0;
    public:
        Menu(Ventana * ventana);
        // virtual ~Menu();
        Figura* getFiguraTexto();
        void cerrar();
        // NOTE Un par de auxiliares que bien podŕian ir en otro lado.
        bool esTecla(SDL_Event * e, SDL_Keycode tecla);
        bool esSalida(SDL_Event * e);
        /* Interacción */
        Menu * getAnterior();
        Menu * getSiguiente();
        virtual int manejarEvento(SDL_Event * e) = 0;
        virtual void accionAnterior() = 0;
        virtual void accionSiguiente() = 0;
        virtual void render();
};

#endif
