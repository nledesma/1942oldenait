#ifndef TEXTODINAMICO_HPP
#define TEXTODINAMICO_HPP
#include "texto.hpp"
class TextoDinamico: public Texto{
    private:
        string caracteres;
    public:
        TextoDinamico(int tamanioFuente, SDL_Color color);
        void cambiarTexto(Ventana* ventana);
        void manejarEvento(SDL_Event evento, Ventana* ventana);
        // void renderizar();
};
#endif
