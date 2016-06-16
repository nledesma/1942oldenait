#ifndef TEXTO_HPP
#define TEXTO_HPP

#include "figura.hpp"
#include "ventana.hpp"
#include <pthread.h>

#define STAR_WARS_FONT "../../resources/fonts/distantGalaxy.ttf"
#define STAR_WARS_FONT2 "../../resources/fonts/distantGalaxy2.ttf"
#define STAR_WARS_SYMBOL "../../resources/fonts/Starjedi.ttf"

#define AMARILLO_STAR_WARS {255, 232, 32}

class Texto {
    protected:
        Figura* texto;
        TTF_Font* fuente;
        SDL_Color color;
        Ventana * ventana;
    public:
        Texto(int tamanioFuente, SDL_Color color, string fuente, Ventana * ventana);
        virtual ~Texto();
        void cargarFuente(string textoString);
        virtual void renderizar(int x, int y);
        void renderDerecho(int x, int y);
        void renderCentrado(int y);
        Figura* getFigura();
        TTF_Font* getFuente();
};

#endif
