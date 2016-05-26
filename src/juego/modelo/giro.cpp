#include "giro.hpp"

void Giro::girarAngulo(float &posX, float &posY, float &velocidad, float &angulo, float &anguloAbarrer,
                       int &estadoAnimacion, float velocidadAngular, float timestep) {

}

void Giro::transportarAngulo(float &angulo, float velocidadAngular, float timestep) {
    angulo = angulo + timestep * velocidadAngular;
    if ( angulo < 0 ){
        angulo = angulo + 360;
    } else if ( angulo > 360 ){
        angulo = angulo - 360;
    }
}