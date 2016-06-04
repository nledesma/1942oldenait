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
    public:
        ListaDeSeleccion();
        void agregarOpcion(string strOpcion, SDL_Renderer* renderer);
        void renderizar(SDL_Renderer* renderer);
};
#endif
