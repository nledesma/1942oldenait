#include "powerUpDosAmetralladorasVista.hpp"

PowerUpDosAmetralladorasVista::~PowerUpDosAmetralladorasVista() { }

PowerUpDosAmetralladorasVista::PowerUpDosAmetralladorasVista() {
    cout << "ENTRO A CREAR EL POWER UP DOS AMETRALLADORAS VISTA" << endl;
    this->figuraPowerUp = new Figura();
    this->pathSprite = SPRITE_POWERUP_DOS_AMETRALLADORAS;

    //Moneda sin rotar
    this->clipsAnimacion[POWER_UP_NORMAL].x = 0;
    this->clipsAnimacion[POWER_UP_NORMAL].y = 0;
    this->clipsAnimacion[POWER_UP_NORMAL].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_NORMAL].h = ALTO_POWERUP;

    //Moneda rotada 1
    this->clipsAnimacion[POWER_UP_ROTACION_1].x = 0 + ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_ROTACION_1].y = 0;
    this->clipsAnimacion[POWER_UP_ROTACION_1].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_ROTACION_1].h = ALTO_POWERUP;


    //Moneda rotada 2
    this->clipsAnimacion[POWER_UP_ROTACION_2].x = 0 + ANCHO_POWERUP * 2;
    this->clipsAnimacion[POWER_UP_ROTACION_2].y = 0;
    this->clipsAnimacion[POWER_UP_ROTACION_2].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_ROTACION_2].h = ALTO_POWERUP;

    //Moneda de canto
    this->clipsAnimacion[POWER_UP_ROTACION_3].x = 0 + ANCHO_POWERUP * 3;
    this->clipsAnimacion[POWER_UP_ROTACION_3].y = 0;
    this->clipsAnimacion[POWER_UP_ROTACION_3].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_ROTACION_3].h = ALTO_POWERUP;

    //Moneda rotada 3
    this->clipsAnimacion[POWER_UP_ROTACION_4].x = 0 + ANCHO_POWERUP * 4;
    this->clipsAnimacion[POWER_UP_ROTACION_4].y = 0;
    this->clipsAnimacion[POWER_UP_ROTACION_4].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_ROTACION_4].h = ALTO_POWERUP;

    //Moneda rotada 4
    this->clipsAnimacion[POWER_UP_ROTACION_5].x = 0 + ANCHO_POWERUP * 5;
    this->clipsAnimacion[POWER_UP_ROTACION_5].y = 0;
    this->clipsAnimacion[POWER_UP_ROTACION_5].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_ROTACION_5].h = ALTO_POWERUP;

    //Moneda normal
    this->clipsAnimacion[POWER_UP_ROTACION_6].x = 0 + ANCHO_POWERUP * 6;
    this->clipsAnimacion[POWER_UP_ROTACION_6].y = 0;
    this->clipsAnimacion[POWER_UP_ROTACION_6].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_ROTACION_6].h = ALTO_POWERUP;

    //Moneda despues de ser colisionada
    this->clipsAnimacion[POWER_UP_COLISIONADO].x = 0;
    this->clipsAnimacion[POWER_UP_COLISIONADO].y = 0 + ALTO_POWERUP;
    this->clipsAnimacion[POWER_UP_COLISIONADO].w = ANCHO_POWERUP;
    this->clipsAnimacion[POWER_UP_COLISIONADO].h = ALTO_POWERUP;

    cout << "TERMINO DE CREAR EL POWER UP DOS AMETRALLADORAS VISTA" << endl;
}

void PowerUpDosAmetralladorasVista::cargarImagen(SDL_Renderer *renderer) {
    cout << "ENTRO A CARGAR LA IMAGEN DE POWER UP DOS AMETRALLADORAS" << endl;
    PowerUpVista::cargarImagen(renderer);
}

void PowerUpDosAmetralladorasVista::render(float posX, float posY, int estadoAnimacion, SDL_Renderer *renderer) {
    cout << "ENTRO A RENDER DE POWER UP DOS AMETRALLADORAS" << endl;
    PowerUpVista::render(posX, posY, estadoAnimacion, renderer);
}
