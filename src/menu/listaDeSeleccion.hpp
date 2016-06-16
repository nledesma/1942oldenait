#ifndef LISTADESELECCION
#define LISTADESELECCION

#include <list>
#include <utility>
#include "radioButton.hpp"
#include "../juego/vista/texto.hpp"
using namespace std;

#define DISTANCIA_BOTONES 40
#define PADDING 40

class ListaDeSeleccion{
    private:
        list <pair <RadioButton*, Texto*> > opciones;
        Ventana * ventana;
        int x, y; // posicion.
        RadioButton * boton(int nroBoton);
        int nroBotonSeleccionado;
        void cambiarSeleccion(int nroBoton);
    public:
        ListaDeSeleccion(Ventana * ventana, int x, int y);
        ~ListaDeSeleccion();
        void agregarOpcion(string strOpcion);
        void manejarEvento(SDL_Event * e);
        void renderizar();
        void clickEn(int x, int y);
        int getNroBotonSeleccionado();
        int getCantidadOpciones();
};

#endif
