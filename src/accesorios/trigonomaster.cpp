#include "trigonomaster.hpp"

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


