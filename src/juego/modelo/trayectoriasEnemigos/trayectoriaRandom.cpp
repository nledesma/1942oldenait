#include "trayectoriaRandom.hpp"

TrayectoriaRandom::~TrayectoriaRandom() { }

TrayectoriaRandom::TrayectoriaRandom() {

}

void TrayectoriaRandom::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion,
                                float timestep) {

    /* Se sortea el siguiente angulo. */
    int dobla = rand() % 250; // Si el resultado esta entre 0 y 5 el avion sigue derecho

    if (dobla == 0 || dobla == 1){
        angulo = angulo - 22.5f;
    } else if (dobla == 2 || dobla == 3){
        angulo = angulo + 22.5f;
    }

    /* Se corrige su valor si se va de rango */
    if ( angulo < 0 ){
        angulo = angulo + 360;
    } else if ( angulo > 360 ){
        angulo = angulo - 360;
    }

    /* Se realiza el siguiente movimiento. */
    float velocidadX = velocidad * Trigonomaster::getCoseno(angulo, estadoAnimacion);
    float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo, estadoAnimacion));

    posX += velocidadX*timestep;
    posY += velocidadY*timestep;
}

void TrayectoriaRandom::setEstadoInicial() {

}
