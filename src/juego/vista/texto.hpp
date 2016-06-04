#ifndef TEXTO_HPP
#define TEXTO_HPP
#include "figura.hpp"
#include "ventana.hpp"
class Texto{
    protected:
        Figura* texto;
        TTF_Font* fuente;
        SDL_Color color;
    public:
        Texto(int tamanioFuente, SDL_Color color);
        void cargarFuente(string textoString, Ventana* ventana);
        virtual void renderizar(int x, int y, SDL_Renderer* renderer);
        Figura* getFigura();
        TTF_Font* getFuente();
        ~Texto();
};

#endif
