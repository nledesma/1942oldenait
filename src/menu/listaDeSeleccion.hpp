#ifndef LISTADESELECCION
#define LISTADESELECCION

#include <list>
#include <utility>
#include "radioButton.hpp"
#include "../juego/vista/texto.hpp"
using namespace std;

class ListaDeSeleccion{
    private:
        list <pair <RadioButton*, Texto*> > opciones;
        Ventana * ventana;
    public:
        ListaDeSeleccion(Ventana * ventana);
        ~ListaDeSeleccion();
        void agregarOpcion(string strOpcion);
        void renderizar();
};

#endif
