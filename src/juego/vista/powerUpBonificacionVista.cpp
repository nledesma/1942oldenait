#include "powerUpBonificacionVista.hpp"

PowerUpBonificacionVista::~PowerUpBonificacionVista() { }

PowerUpBonificacionVista::PowerUpBonificacionVista() {
    this->figuraPowerUp = new Figura();
    this->pathSprite = SPRITE_POWERUP_BONIFICACION;

    //Moneda sin rotar
    this->clipsAnimacion[POWER_UP_BONIFICACION_NORMAL].x = 0;
    this->clipsAnimacion[POWER_UP_BONIFICACION_NORMAL].y = 0;
    this->clipsAnimacion[POWER_UP_BONIFICACION_NORMAL].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_NORMAL].h = ALTO_POWERUP;

    //Moneda rotada 1
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_1].x = 0 + ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_1].y = 0;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_1].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_1].h = ALTO_POWERUP;

    //Moneda rotada 2
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_2].x = 0 + ANCHO_POWERUP * 2;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_2].y = 0;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_2].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_2].h = ALTO_POWERUP;

    //Moneda de canto
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_3].x = 0 + ANCHO_POWERUP * 3;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_3].y = 0;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_3].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_3].h = ALTO_POWERUP;

    //Moneda rotada 3
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_4].x = 0 + ANCHO_POWERUP * 4;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_4].y = 0;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_4].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_4].h = ALTO_POWERUP;

    //Moneda rotada 4
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_5].x = 0;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_5].y = 0 + ALTO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_5].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_5].h = ALTO_POWERUP;

    //Moneda normal 
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_6].x = 0 + ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_6].y = 0 + ALTO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_6].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_ROTACION_6].h = ALTO_POWERUP;

    //Moneda despues de ser colisionada
    this->clipsAnimacion[POWER_UP_BONIFICACION_COLISIONADO].x = 0 + ANCHO_POWERUP * 2;
    this->clipsAnimacion[POWER_UP_BONIFICACION_COLISIONADO].y = 0 + ALTO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_COLISIONADO].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_BONIFICACION_COLISIONADO].h = ALTO_POWERUP;
}

void PowerUpBonificacionVista::cargarImagen(SDL_Renderer *renderer) {
    PowerUpVista::cargarImagen(renderer);
}

void PowerUpBonificacionVista::render(float posX, float posY, int estadoAnimacion, SDL_Renderer *renderer) {
    PowerUpVista::render(posX, posY, estadoAnimacion, renderer);
}
