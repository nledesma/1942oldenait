#ifndef TEXTODINAMICO_HPP
#define TEXTODINAMICO_HPP

#include "texto.hpp"

class TextoDinamico: public Texto{
    private:
        string caracteres;
        void recargarTexto();
    public:
        TextoDinamico(int tamanioFuente, SDL_Color color, Ventana * ventana);
        void cambiarTexto(string textoNuevo);
        void manejarEvento(SDL_Event evento);
        string getTexto();
};

#endif
