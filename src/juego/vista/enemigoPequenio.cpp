#include "enemigoPequenio.hpp"

EnemigoPequenio::~EnemigoPequenio() { }

EnemigoPequenio::EnemigoPequenio() {
    this->figuraEnemigo = new Figura();
    this->pathSprite = SPRITE_AVION_ENEMIGO_PEQUENIO;

    //Avión 90º
    this->clipsAnimacion[AVION_ENEMIGO_90G].x = 0;
    this->clipsAnimacion[AVION_ENEMIGO_90G].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_90G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_90G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 67,5º
    this->clipsAnimacion[AVION_ENEMIGO_67G].x = 0 + ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_67G].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_67G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_67G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 45º
    this->clipsAnimacion[AVION_ENEMIGO_45G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_45G].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_45G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_45G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 2,5º
    this->clipsAnimacion[AVION_ENEMIGO_22G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 3;
    this->clipsAnimacion[AVION_ENEMIGO_22G].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_22G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_22G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 0º
    this->clipsAnimacion[AVION_ENEMIGO_0G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_0G].y = 0;
    this->clipsAnimacion[AVION_ENEMIGO_0G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_0G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 337,5º
    this->clipsAnimacion[AVION_ENEMIGO_337G].x = 0;
    this->clipsAnimacion[AVION_ENEMIGO_337G].y = 0 + ALTO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_337G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_337G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 315º
    this->clipsAnimacion[AVION_ENEMIGO_315G].x = 0 + ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_315G].y = 0 + ALTO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_315G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_315G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 292,5º
    this->clipsAnimacion[AVION_ENEMIGO_292G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_292G].y = 0 + ALTO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_292G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_292G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 270º
    this->clipsAnimacion[AVION_ENEMIGO_270G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 3;
    this->clipsAnimacion[AVION_ENEMIGO_270G].y = 0 + ALTO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_270G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_270G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 247,5º
    this->clipsAnimacion[AVION_ENEMIGO_247G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_247G].y = 0 + ALTO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_247G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_247G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 225º
    this->clipsAnimacion[AVION_ENEMIGO_225G].x = 0;
    this->clipsAnimacion[AVION_ENEMIGO_225G].y = 0 + ALTO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_225G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_225G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 202,5º
    this->clipsAnimacion[AVION_ENEMIGO_202G].x = 0 + ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_202G].y = 0 + ALTO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_202G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_202G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 180º
    this->clipsAnimacion[AVION_ENEMIGO_180G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_180G].y = 0 + ALTO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_180G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_180G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 157,5º
    this->clipsAnimacion[AVION_ENEMIGO_157G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 3;
    this->clipsAnimacion[AVION_ENEMIGO_157G].y = 0 + ALTO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_157G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_157G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 135º
    this->clipsAnimacion[AVION_ENEMIGO_135G].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_135G].y = 0 + ALTO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_135G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_135G].h = ALTO_ENEMIGO_PEQUENIO;

    //Avión 112,5º
    this->clipsAnimacion[AVION_ENEMIGO_112G].x = 0;
    this->clipsAnimacion[AVION_ENEMIGO_112G].y = 0 + ALTO_ENEMIGO_PEQUENIO * 3;
    this->clipsAnimacion[AVION_ENEMIGO_112G].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_112G].h = ALTO_ENEMIGO_PEQUENIO;

    //Flip etapa 1
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_1].x = 0 ;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_1].y = 0 + ALTO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_1].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_1].h = ALTO_ENEMIGO_PEQUENIO;

    //Flip etapa 2
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_2].x = 0 + ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_2].y = 0 + ALTO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_2].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_2].h = ALTO_ENEMIGO_PEQUENIO;

    //Flip etapa 3
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_3].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_3].y = 0 + ALTO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_3].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_3].h = ALTO_ENEMIGO_PEQUENIO;

    //Flip etapa 4
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_4].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 3;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_4].y = 0 + ALTO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_4].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_4].h = ALTO_ENEMIGO_PEQUENIO;

    //Flip etapa 5
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_5].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_5].y = 0 + ALTO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_5].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_5].h = ALTO_ENEMIGO_PEQUENIO;

    //Flip etapa 6
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_6].x = 0;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_6].y = 0 + ALTO_ENEMIGO_PEQUENIO * 5;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_6].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_6].h = ALTO_ENEMIGO_PEQUENIO;

    //Flip etapa 7
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_7].x = 0 + ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_7].y = 0 + ALTO_ENEMIGO_PEQUENIO * 5;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_7].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_FLIP_ETAPA_7].h = ALTO_ENEMIGO_PEQUENIO;

    //Explosión etapa 1
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_1].x = 0 ;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_1].y = 0 + ALTO_ENEMIGO_PEQUENIO * 6;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_1].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_1].h = ALTO_ENEMIGO_PEQUENIO;

    //Explosión etapa 2
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_2].x = 0 + ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_2].y = 0 + ALTO_ENEMIGO_PEQUENIO * 6;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_2].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_2].h = ALTO_ENEMIGO_PEQUENIO;

    //Explosión etapa 3
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_3].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 2;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_3].y = 0 + ALTO_ENEMIGO_PEQUENIO * 6;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_3].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_3].h = ALTO_ENEMIGO_PEQUENIO;

    //Explosión etapa 4
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_4].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 3;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_4].y = 0 + ALTO_ENEMIGO_PEQUENIO * 6;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_4].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_4].h = ALTO_ENEMIGO_PEQUENIO;

    //Explosión etapa 5
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_5].x = 0 + ANCHO_ENEMIGO_PEQUENIO * 4;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_5].y = 0 + ALTO_ENEMIGO_PEQUENIO * 6;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_5].w = ANCHO_ENEMIGO_PEQUENIO;
    this->clipsAnimacion[AVION_ENEMIGO_EXPLOSION_ETAPA_5].h = ALTO_ENEMIGO_PEQUENIO;
}

void EnemigoPequenio::cargarImagen(SDL_Renderer *renderer) {
    EnemigoVista::cargarImagen(renderer);
}

void EnemigoPequenio::render(float posX, float posY, int estadoAnimacion, SDL_Renderer *renderer) {
    EnemigoVista::render(posX, posY, estadoAnimacion, renderer);
}
