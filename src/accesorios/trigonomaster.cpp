#include "trigonomaster.hpp"

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
            anguloAnimacion = 5;
            break;
        case 1:
            valor = 0.9238795325;
            anguloAnimacion = 4;
            break;
        case 2:
            valor = 0.7071067812;
            anguloAnimacion = 3;
            break;
        case 3:
            valor = 0.3826834324;
            anguloAnimacion = 2;
            break;
        case 4:
            valor = 0;
            anguloAnimacion = 1;
            break;
        case 5:
            valor = -0.3826834324;
            anguloAnimacion = 16;
            break;
        case 6:
            valor = -0.7071067812;
            anguloAnimacion = 15;
            break;
        case 7:
            valor = -0.9238795325;
            anguloAnimacion = 14;
            break;
        case 8:
            valor = -1;
            anguloAnimacion = 13;
            break;
        case 9:
            valor = -0.9238795325;
            anguloAnimacion = 12;
            break;
        case 10:
            valor = -0.7071067812;
            anguloAnimacion = 11;
            break;
        case 11:
            valor = -0.3826834324;
            anguloAnimacion = 10;
            break;
        case 12:
            valor = 0;
            anguloAnimacion = 9;
            break;
        case 13:
            valor = 0.3826834324;
            anguloAnimacion = 8;
            break;
        case 14:
            valor = 0.7071067812;
            anguloAnimacion = 7;
            break;
        case 15:
            valor = 0.9238795325;
            anguloAnimacion = 6;
            break;
        case 16:
            valor = 1;
            anguloAnimacion = 5;
            break;
        default:
            valor = 1;
            anguloAnimacion = 5;
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
            anguloAnimacion = 5;
            break;
        case 1:
            anguloAnimacion = 4;
            break;
        case 2:
            anguloAnimacion = 3;
            break;
        case 3:
            anguloAnimacion = 2;
            break;
        case 4:
            anguloAnimacion = 1;
            break;
        case 5:
            anguloAnimacion = 16;
            break;
        case 6:
            anguloAnimacion = 15;
            break;
        case 7:
            anguloAnimacion = 14;
            break;
        case 8:
            anguloAnimacion = 13;
            break;
        case 9:
            anguloAnimacion = 12;
            break;
        case 10:
            anguloAnimacion = 11;
            break;
        case 11:
            anguloAnimacion = 10;
            break;
        case 12:
            anguloAnimacion = 9;
            break;
        case 13:
            anguloAnimacion = 8;
            break;
        case 14:
            anguloAnimacion = 7;
            break;
        case 15:
            anguloAnimacion = 6;
            break;
        case 16:
            anguloAnimacion = 5;
            break;
        default:
            anguloAnimacion = 5;
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
            anguloAnimacion = 5;
            break;
        case 1:
            valor = 0.3826834324;
            anguloAnimacion = 4;
            break;
        case 2:
            valor = 0.7071067812;
            anguloAnimacion = 3;
            break;
        case 3:
            valor = 0.9238795325;
            anguloAnimacion = 2;
            break;
        case 4:
            valor = 1;
            anguloAnimacion = 1;
            break;
        case 5:
            valor = 0.9238795325;
            anguloAnimacion = 16;
            break;
        case 6:
            valor = 0.7071067812;
            anguloAnimacion = 15;
            break;
        case 7:
            valor = 0.3826834324;
            anguloAnimacion = 14;
            break;
        case 8:
            valor = 0;
            anguloAnimacion = 13;
            break;
        case 9:
            valor = -0.3826834324;
            anguloAnimacion = 12;
            break;
        case 10:
            valor = -0.7071067812;
            anguloAnimacion = 11;
            break;
        case 11:
            valor = -0.9238795325;
            anguloAnimacion = 10;
            break;
        case 12:
            valor = -1;
            anguloAnimacion = 9;
            break;
        case 13:
            valor = -0.9238795325;
            anguloAnimacion = 8;
            break;
        case 14:
            valor = -0.7071067812;
            anguloAnimacion = 7;
            break;
        case 15:
            valor = -0.3826834324;
            anguloAnimacion = 6;
            break;
        case 16:
            valor = 0;
            anguloAnimacion = 5;
            break;
        default:
            valor = 0;
            anguloAnimacion = 5;
    }
    return (float) valor;
}


