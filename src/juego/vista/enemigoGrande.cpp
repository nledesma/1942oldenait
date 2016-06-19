#include "enemigoGrande.hpp"

EnemigoGrande::~EnemigoGrande() { }

EnemigoGrande::EnemigoGrande() {
    this->figuraEnemigo = new Figura();
    this->pathSprite = SPRITE_AVION_ENEMIGO_GRANDE;

    //Avión normal
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_NORMAL].x = 0;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_NORMAL].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_NORMAL].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_NORMAL].h = ALTO_ENEMIGO_GRANDE;

    //Avión dañado parte 1
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_DANIADO_1].x = 0 + ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_DANIADO_1].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_DANIADO_1].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_DANIADO_1].h = ALTO_ENEMIGO_GRANDE;

    //Avión dañado parte 2
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_DANIADO_2].x = 0 + ANCHO_ENEMIGO_GRANDE * 2;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_DANIADO_2].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_DANIADO_2].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_DANIADO_2].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 1
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1].x = 0 + ANCHO_ENEMIGO_GRANDE * 3;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 2
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_2].x = 0 + ANCHO_ENEMIGO_GRANDE * 4;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_2].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_2].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_2].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 3
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_3].x = 0;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_3].y = 0 + ALTO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_3].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_3].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 4
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_4].x = 0 + ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_4].y = 0 + ALTO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_4].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_4].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 5
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_5].x = 0 + ANCHO_ENEMIGO_GRANDE * 2;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_5].y = 0 + ALTO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_5].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_5].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 6
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_6].x = 0 + ANCHO_ENEMIGO_GRANDE * 3;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_6].y = 0 + ALTO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_6].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_6].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 7
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_7].x = 0 + ANCHO_ENEMIGO_GRANDE * 4;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_7].y = 0 + ALTO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_7].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_7].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 8
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_8].x = 0;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_8].y = 0 + ALTO_ENEMIGO_GRANDE * 2;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_8].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_8].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 9
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_9].x = 0 + ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_9].y = 0 + ALTO_ENEMIGO_GRANDE * 2;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_9].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_9].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 10
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_10].x = 0 + ANCHO_ENEMIGO_GRANDE * 2;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_10].y = 0 + ALTO_ENEMIGO_GRANDE * 2;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_10].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_10].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 11
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_11].x = 0 + ANCHO_ENEMIGO_GRANDE * 3;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_11].y = 0 + ALTO_ENEMIGO_GRANDE * 2;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_11].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_11].h = ALTO_ENEMIGO_GRANDE;

    //Avión explosion etapa 12
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_12].x = 0 + ANCHO_ENEMIGO_GRANDE * 4;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_12].y = 0 + ALTO_ENEMIGO_GRANDE * 2;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_12].w = ANCHO_ENEMIGO_GRANDE;
    this->clipsAnimacion[AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_12].h = ALTO_ENEMIGO_GRANDE;
}

void EnemigoGrande::cargarImagen(SDL_Renderer *renderer) {
    EnemigoVista::cargarImagen(renderer);
}

void EnemigoGrande::render(float posX, float posY, int estadoAnimacion, SDL_Renderer *renderer) {
    EnemigoVista::render(posX, posY, estadoAnimacion, renderer);
}