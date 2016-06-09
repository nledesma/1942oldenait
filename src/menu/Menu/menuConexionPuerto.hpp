#ifndef MENUCONEXIONPUERTO_H
#define MENUCONEXIONPUERTO_H

#include "../Boton/botonSiguiente.hpp"
#include "menu.hpp"
using namespace std;

class MenuConexionPuerto: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        Texto* textoPuerto;
    public:
        MenuConexionPuerto();
        bool cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        void cerrar();
};

#endif
