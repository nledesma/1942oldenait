#ifndef MENUCONEXIONPUERTO_H
#define MENUCONEXIONPUERTO_H

#include "../Boton/boton.hpp"
#include "menu.hpp"
using namespace std;

class MenuConexionPuerto: public Menu{
    private:
        Boton* botonSiguiente;
        Texto* textoPuerto;
    public:
        MenuConexionPuerto();
        void cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        Boton* getBotonSiguiente();
        void cerrar();
};

#endif
