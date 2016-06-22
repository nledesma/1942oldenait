#ifndef MENUCONEXIONES_H
#define MENUCONEXIONES_H

#include "menuLista.hpp"
#include "../../../../net/cliente/clienteParser.hpp"
using namespace std;

class MenuConexiones: public MenuLista {
    private:
        Menu * menuPorEquipos;
        Menu * menuConexionManual;
        Cliente * cliente;
        list<Conexion> conexionesGuardadas;
        Aviso * aviso;
    public:
        MenuConexiones(Ventana* ventana, Cliente * cliente);
        ~MenuConexiones();
        void agregarOpciones();
        void setMenuConexionManual(Menu * m);
        void setMenuDatosUsuario(Menu * m);
        void setMenuPorEquipos(Menu * m);
        int manejarEvento(SDL_Event * e);
        void accionAnterior();
        void accionSiguiente();
        bool conectar(string ip, int puerto);
        void render();
};

#endif
