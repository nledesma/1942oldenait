#ifndef MENUMODOSDEJUEGO_H
#define MENUMODOSDEJUEGO_H

#include "../Boton/botonJugar.hpp"
#include "../Boton/botonSalir.hpp"
#include "../Boton/botonEnColaboracion.hpp"
#include "../Boton/botonPorEquipos.hpp"
#include "../Boton/botonModoPractica.hpp"
#include "menu.hpp"
using namespace std;

class MenuModosDeJuego: public Menu{
    private:
        BotonEnColaboracion* botonEnColaboracion;
        BotonPorEquipos* botonPorEquipos;
        BotonModoPractica* botonModoPractica;
        Texto* texto;
    public:
        MenuModosDeJuego();
        bool cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonEnColaboracion* getBotonEnColaboracion();
        BotonPorEquipos* getBotonPorEquipos();
        BotonModoPractica* getBotonModoPractica();
        void cerrar();

};

#endif
