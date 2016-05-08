#include "decodificador.hpp"
#include <iostream>

/* Push y pop de Strings de ids de sprites e imágenes */

void Decodificador::push(string &codigo, string idImg) {
    push(codigo, (char) idImg.length());
    codigo += idImg;
}

string Decodificador::popIdImg(string &codigo) {
    string lengthString = popBytes(codigo, sizeof(char));
    int length = (int) lengthString[0];
    return popBytes(codigo, length);
}

/* Push y pop de Elementos del mapa. */
void Decodificador::push(string & codigo, Elemento *e) {
    // pos_x (1 float) | pos_y (1 float)
    push(codigo, e->getPosX());
    push(codigo, e->getPosY());
}

string Decodificador::popElemento(string & codigo) {
    return popBytes(codigo, 2 * sizeof(float));
}

/* Push y pop de Aviones. */
void Decodificador::push(string & codigo, Avion* a) {
    // posX, posY (2 floats) | estadoAnimacion (1 byte)
    push(codigo, a->getPosicionX());
    push(codigo, a->getPosicionY());
    push(codigo, (char) a->getEstadoAnimacion());
}

string Decodificador::popAvion(string & codigo){
    return popBytes(codigo, 2*sizeof(float) + 1);
}

/* Push y pop de disparo. */
void Decodificador::push(string & codigo, Disparo *d) {
    // posX, posY (2 floats)
    push(codigo, d->getPosX());
    push(codigo, d->getPosY());
}

string Decodificador::popDisparo(string & codigo) {
    return popBytes(codigo, 2*sizeof(float));
}

/* Push y Pop del Escenario. */
void Decodificador::push(string & codigo, EscenarioJuego *e) {
    // Offset (float)
    push(codigo, e->getOffset());
}

string Decodificador::popEscenario(string &codigo){
    return popBytes(codigo, sizeof(float));
}

/* Generales para cualquier tipo */
template<typename T> void Decodificador::push(string & str, T e) {
    int n = sizeof(e);
    char * bytes = new char[n];
    memcpy((void*)bytes, (void*) &e, n);

    for (int i = 0; i < n; i++) {
        str += bytes[i];
    }

    delete bytes;
}

string Decodificador::popBytes(string & codigo, int cBytes) {
    string ret = codigo.substr(0, cBytes);
    codigo.erase(0, cBytes);
    return ret;
}

void Decodificador::imprimirBytes(string codigo) {
    for (int i = 0; i < codigo.length(); ++i) {
        cout << (int) codigo[i] << " ";
    }
    cout << endl;
}

void Decodificador::pushInicial(string &codigo, Avion *a) {
    push(codigo, a->getPosicionX());
    push(codigo, a->getPosicionY());
    push(codigo, a->getIdSprite());
}

void Decodificador::pushInicial(string &codigo, Elemento *e) {
    push(codigo, e->getPosX());
    push(codigo, e->getPosY());
    push(codigo, e->getIdSprite());
}

void Decodificador::pushInicial(string &codigo, EscenarioJuego *e) {
    push(codigo , e->getAncho());
    push(codigo, e->getAlto());
    push(codigo, e->getIdSprite());
}

void Decodificador::pushInicialDisparo(string &codigo, string idSpriteDisparo) {
    push(codigo, idSpriteDisparo);
}

