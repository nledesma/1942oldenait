#include "trayectoriaIdaYvuelta.hpp"
#include "../../../accesorios/codigo.hpp"

TrayectoriaIdaYvuelta::~TrayectoriaIdaYvuelta() { }

TrayectoriaIdaYvuelta::TrayectoriaIdaYvuelta() {
    this->tiempoIda = 3.5;
}

void TrayectoriaIdaYvuelta::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion,
                              float timestep) {

    estadoAnimacion = AVION_ENEMIGO_270G;
    /* Se realiza el siguiente movimiento. */
    float velocidadX = velocidad * Trigonomaster::getCoseno(angulo);
    float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo));
    float velocidadYFinal = velocidadY;
    if (tiempoIda < 0.75) {
        velocidadYFinal = velocidadY * tiempoIda;
        if (tiempoIda > 0.6){
            estadoAnimacion = AVION_ENEMIGO_FLIP_ETAPA_1;
        } else if (tiempoIda > 0.3) {
            estadoAnimacion = AVION_ENEMIGO_FLIP_ETAPA_2;
        } else if (tiempoIda > 0.1) {
            estadoAnimacion = AVION_ENEMIGO_FLIP_ETAPA_3;
        } else if (tiempoIda > - 0.1) {
            estadoAnimacion = AVION_ENEMIGO_FLIP_ETAPA_4;
        } else if (tiempoIda > - 0.3){
            estadoAnimacion = AVION_ENEMIGO_FLIP_ETAPA_5;
        } else if (tiempoIda > - 0.6){
            estadoAnimacion = AVION_ENEMIGO_FLIP_ETAPA_6;
        } else if (tiempoIda > - 0.75){
            estadoAnimacion = AVION_ENEMIGO_FLIP_ETAPA_7;
        }
    }
    if (tiempoIda <= -0.75) {
        velocidadYFinal = - velocidadY;
        estadoAnimacion = AVION_ENEMIGO_90G;
    }

    posX += velocidadX*timestep;
    posY += velocidadYFinal*timestep;

    this->tiempoIda = this->tiempoIda - timestep;
}

void TrayectoriaIdaYvuelta::setEstadoInicial() {
    this->tiempoIda = 3.5;
}
