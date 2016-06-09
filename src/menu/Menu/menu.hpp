#ifndef MENU_H
#define MENU_H

#include "../Boton/botonJugar.hpp"
#include "../Boton/botonSalir.hpp"
#include "../../juego/vista/ventana.hpp"
#include "../../juego/vista/texto.hpp"
#include <list>
using namespace std;

class Menu{
    private:
        TTF_Font *gFont;
        Figura* textTexture;
    protected:
        Figura* fondo;
        virtual bool cargarBotones(Ventana* ventana) = 0;
        virtual void renderizar(Ventana* ventana) = 0;
    public:
        Menu();
        Figura* getFiguraTexto();
        void cerrar();
};

#endif
