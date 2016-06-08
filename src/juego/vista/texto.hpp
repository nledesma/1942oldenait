#ifndef TEXTO_HPP
#define TEXTO_HPP
#include "figura.hpp"
#include "ventana.hpp"

#define STAR_WARS_FONT "../../resources/fonts/STARWARS.ttf"

class Texto {
    protected:
        Figura* texto;
        TTF_Font* fuente;
        SDL_Color color;
        Ventana * ventana;
    public:
        Texto(int tamanioFuente, SDL_Color color, Ventana * ventana);
        virtual ~Texto();
        void cargarFuente(string textoString);
        virtual void renderizar(int x, int y);
        Figura* getFigura();
        TTF_Font* getFuente();
};

#endif
