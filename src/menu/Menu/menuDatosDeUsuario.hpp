#ifndef MENUDATOSDEUSUARIO_H
#define MENUDATOSDEUSUARIO_H

#include "menu.hpp"
#include "../Boton/botonSiguiente.hpp"
using namespace std;

class MenuDatosDeUsuario: public Menu{
    private:
        BotonSiguiente* botonSiguiente;
        TTF_Font* fuenteAlias;
    	TTF_Font* fuenteTitulo;
        Figura* figuraFuenteAlias;
    	Figura* figuraFuenteTitulo;
    public:
        MenuDatosDeUsuario();
        bool cargarBotones(Ventana* ventana);
        void renderizar(Ventana* ventana);
        BotonSiguiente* getBotonSiguiente();
        TTF_Font* getFuenteAlias();
        TTF_Font* getFuenteTitulo();
        Figura* getFiguraFuenteAlias();
        Figura* getFiguraFuenteTitulo();
        void cerrar();

};

#endif
