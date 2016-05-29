#include "trigonomaster.hpp"
#include "codigo.hpp"
#include <iostream>

using namespace std;

float Trigonomaster::getCoseno(float angulo, int &anguloAnimacion) {
    double porcionAngular = PORCION_ANGULO * angulo;
    int porcionAngularEntera = (int) floor(porcionAngular);
    double parteDecimal = porcionAngular - porcionAngularEntera;
    if (parteDecimal >= 0.5){
        porcionAngularEntera = porcionAngularEntera + 1;
    }
    double valor;
    switch (porcionAngularEntera){
        case 0:
            valor = 1;
            anguloAnimacion = AVION_ENEMIGO_0G;
            break;
        case 1:
            valor = 0.9238795325;
            anguloAnimacion = AVION_ENEMIGO_22G;
            break;
        case 2:
            valor = 0.7071067812;
            anguloAnimacion = AVION_ENEMIGO_45G;
            break;
        case 3:
            valor = 0.3826834324;
            anguloAnimacion = AVION_ENEMIGO_67G;
            break;
        case 4:
            valor = 0;
            anguloAnimacion = AVION_ENEMIGO_90G;
            break;
        case 5:
            valor = -0.3826834324;
            anguloAnimacion = AVION_ENEMIGO_112G;
            break;
        case 6:
            valor = -0.7071067812;
            anguloAnimacion = AVION_ENEMIGO_135G;
            break;
        case 7:
            valor = -0.9238795325;
            anguloAnimacion = AVION_ENEMIGO_157G;
            break;
        case 8:
            valor = -1;
            anguloAnimacion = AVION_ENEMIGO_180G;
            break;
        case 9:
            valor = -0.9238795325;
            anguloAnimacion = AVION_ENEMIGO_202G;
            break;
        case 10:
            valor = -0.7071067812;
            anguloAnimacion = AVION_ENEMIGO_225G;
            break;
        case 11:
            valor = -0.3826834324;
            anguloAnimacion = AVION_ENEMIGO_247G;
            break;
        case 12:
            valor = 0;
            anguloAnimacion = AVION_ENEMIGO_270G;
            break;
        case 13:
            valor = 0.3826834324;
            anguloAnimacion = AVION_ENEMIGO_292G;
            break;
        case 14:
            valor = 0.7071067812;
            anguloAnimacion = AVION_ENEMIGO_315G;
            break;
        case 15:
            valor = 0.9238795325;
            anguloAnimacion = AVION_ENEMIGO_337G;
            break;
        case 16:
            valor = 1;
            anguloAnimacion = AVION_ENEMIGO_0G;
            break;
        default:
            valor = 1;
            anguloAnimacion = AVION_ENEMIGO_0G;
    }
    return (float) valor;
}

float Trigonomaster::getCoseno(float angulo) {
    double porcionAngular = PORCION_ANGULO * angulo;
    int porcionAngularEntera = (int) floor(porcionAngular);
    double parteDecimal = porcionAngular - porcionAngularEntera;
    if (parteDecimal >= 0.5){
        porcionAngularEntera = porcionAngularEntera + 1;
    }
    double valor;
    switch (porcionAngularEntera){
        case 0:
            valor = 1;
            break;
        case 1:
            valor = 0.9238795325;
            break;
        case 2:
            valor = 0.7071067812;
            break;
        case 3:
            valor = 0.3826834324;
            break;
        case 4:
            valor = 0;
            break;
        case 5:
            valor = -0.3826834324;
            break;
        case 6:
            valor = -0.7071067812;
            break;
        case 7:
            valor = -0.9238795325;
            break;
        case 8:
            valor = -1;
            break;
        case 9:
            valor = -0.9238795325;
            break;
        case 10:
            valor = -0.7071067812;
            break;
        case 11:
            valor = -0.3826834324;
            break;
        case 12:
            valor = 0;
            break;
        case 13:
            valor = 0.3826834324;
            break;
        case 14:
            valor = 0.7071067812;
            break;
        case 15:
            valor = 0.9238795325;
            break;
        case 16:
            valor = 1;
            break;
        default:
            valor = 1;
    }
    return (float) valor;
}

float Trigonomaster::getSeno(float angulo) {
    double porcionAngular = PORCION_ANGULO * angulo;
    int porcionAngularEntera = (int) floor(porcionAngular);
    double parteDecimal = porcionAngular - porcionAngularEntera;
    if (parteDecimal >= 0.5){
        porcionAngularEntera = porcionAngularEntera + 1;
    }
    double valor;
    switch (porcionAngularEntera){
        case 0:
            valor = 0;
            break;
        case 1:
            valor = 0.3826834324;
            break;
        case 2:
            valor = 0.7071067812;
            break;
        case 3:
            valor = 0.9238795325;
            break;
        case 4:
            valor = 1;
            break;
        case 5:
            valor = 0.9238795325;
            break;
        case 6:
            valor = 0.7071067812;
            break;
        case 7:
            valor = 0.3826834324;
            break;
        case 8:
            valor = 0;
            break;
        case 9:
            valor = -0.3826834324;
            break;
        case 10:
            valor = -0.7071067812;
            break;
        case 11:
            valor = -0.9238795325;
            break;
        case 12:
            valor = -1;
            break;
        case 13:
            valor = -0.9238795325;
            break;
        case 14:
            valor = -0.7071067812;
            break;
        case 15:
            valor = -0.3826834324;
            break;
        case 16:
            valor = 0;
            break;
        default:
            valor = 0;
    }
    return (float) valor;
}

int Trigonomaster::getSpriteAngulo(float angulo) {
    double porcionAngular = PORCION_ANGULO * angulo;
    int porcionAngularEntera = (int) floor(porcionAngular);
    double parteDecimal = porcionAngular - porcionAngularEntera;
    if (parteDecimal >= 0.5){
        porcionAngularEntera = porcionAngularEntera + 1;
    }
    int anguloAnimacion;
    switch (porcionAngularEntera){
        case 0:
            anguloAnimacion = AVION_ENEMIGO_0G;
            break;
        case 1:
            anguloAnimacion = AVION_ENEMIGO_22G;
            break;
        case 2:
            anguloAnimacion = AVION_ENEMIGO_45G;
            break;
        case 3:
            anguloAnimacion = AVION_ENEMIGO_67G;
            break;
        case 4:
            anguloAnimacion = AVION_ENEMIGO_90G;
            break;
        case 5:
            anguloAnimacion = AVION_ENEMIGO_112G;
            break;
        case 6:
            anguloAnimacion = AVION_ENEMIGO_135G;
            break;
        case 7:
            anguloAnimacion = AVION_ENEMIGO_157G;
            break;
        case 8:
            anguloAnimacion = AVION_ENEMIGO_180G;
            break;
        case 9:
            anguloAnimacion = AVION_ENEMIGO_202G;
            break;
        case 10:
            anguloAnimacion = AVION_ENEMIGO_225G;
            break;
        case 11:
            anguloAnimacion = AVION_ENEMIGO_247G;
            break;
        case 12:
            anguloAnimacion = AVION_ENEMIGO_270G;
            break;
        case 13:
            anguloAnimacion = AVION_ENEMIGO_292G;
            break;
        case 14:
            anguloAnimacion = AVION_ENEMIGO_315G;
            break;
        case 15:
            anguloAnimacion = AVION_ENEMIGO_337G;
            break;
        case 16:
            anguloAnimacion = AVION_ENEMIGO_0G;
            break;
        default:
            anguloAnimacion = AVION_ENEMIGO_0G;
    }
    return anguloAnimacion;
}


float Trigonomaster::getSeno(float angulo, int &anguloAnimacion) {
    double porcionAngular = PORCION_ANGULO * angulo;

    int porcionAngularEntera = (int) floor(porcionAngular);
    double parteDecimal = porcionAngular - porcionAngularEntera;
    if (parteDecimal >= 0.5){
        porcionAngularEntera = porcionAngularEntera + 1;
    }
    double valor;
    switch (porcionAngularEntera){
        case 0:
            valor = 0;
            anguloAnimacion = AVION_ENEMIGO_0G;
            break;
        case 1:
            valor = 0.3826834324;
            anguloAnimacion = AVION_ENEMIGO_22G;
            break;
        case 2:
            valor = 0.7071067812;
            anguloAnimacion = AVION_ENEMIGO_45G;
            break;
        case 3:
            valor = 0.9238795325;
            anguloAnimacion = AVION_ENEMIGO_67G;
            break;
        case 4:
            valor = 1;
            anguloAnimacion = AVION_ENEMIGO_90G;
            break;
        case 5:
            valor = 0.9238795325;
            anguloAnimacion = AVION_ENEMIGO_112G;
            break;
        case 6:
            valor = 0.7071067812;
            anguloAnimacion = AVION_ENEMIGO_135G;
            break;
        case 7:
            valor = 0.3826834324;
            anguloAnimacion = AVION_ENEMIGO_157G;
            break;
        case 8:
            valor = 0;
            anguloAnimacion = AVION_ENEMIGO_180G;
            break;
        case 9:
            valor = -0.3826834324;
            anguloAnimacion = AVION_ENEMIGO_202G;
            break;
        case 10:
            valor = -0.7071067812;
            anguloAnimacion = AVION_ENEMIGO_225G;
            break;
        case 11:
            valor = -0.9238795325;
            anguloAnimacion = AVION_ENEMIGO_247G;
            break;
        case 12:
            valor = -1;
            anguloAnimacion = AVION_ENEMIGO_270G;
            break;
        case 13:
            valor = -0.9238795325;
            anguloAnimacion = AVION_ENEMIGO_292G;
            break;
        case 14:
            valor = -0.7071067812;
            anguloAnimacion = AVION_ENEMIGO_315G;
            break;
        case 15:
            valor = -0.3826834324;
            anguloAnimacion = AVION_ENEMIGO_337G;
            break;
        case 16:
            valor = 0;
            anguloAnimacion = AVION_ENEMIGO_0G;
            break;
        default:
            valor = 0;
            anguloAnimacion = AVION_ENEMIGO_0G;
    }
    return (float) valor;
}


