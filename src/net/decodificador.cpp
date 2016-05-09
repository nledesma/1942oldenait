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

/*Push y Pop de Eventos*/
void Decodificador::pushEvento(string & codigo, int evento){
	push(codigo, evento);
}

string Decodificador::popEvento(string & codigo){
    return popBytes(codigo, sizeof(int));
}

string Decodificador::popCantidad(string & codigo){
    return popBytes(codigo, sizeof(int));
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

int Decodificador::stringToInt(string codigo){
    int valorConvertido;
    memcpy((void*)&valorConvertido, (void*)&codigo[0], sizeof(int));
    return valorConvertido;
}

float Decodificador::stringToFloat(string codigo){
    float valorConvertido;
    memcpy((void*)&valorConvertido, (void*)&codigo[0], sizeof(float));
    return valorConvertido;
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

void Decodificador::pushCantidad(string &codigo, int cantidad) {
    push(codigo, cantidad);
}

string Decodificador::popAvionInicial(string & codigo){
    return popBytes(codigo, 2*sizeof(float)) + popIdImg(codigo);
}

string Decodificador::popElementoInicial(string & codigo){
    return popBytes(codigo, 2*sizeof(float)) + popIdImg(codigo);
}

string Decodificador::popEscenarioInicial(string & codigo){
    return popBytes(codigo, 2*sizeof(int)) + popIdImg(codigo);
}

string Decodificador::popDisparoInicial(string &codigo) {
    return popIdImg(codigo);
}

string Decodificador::getCodigoEstadoInicial(EscenarioJuego * escenarioJuego) {
    string codigo;
    Decodificador::pushInicial(codigo, escenarioJuego);
    list<Avion*> aviones = escenarioJuego->getAviones();
    Decodificador::pushCantidad(codigo, (int) aviones.size());
    for(list<Avion*>::iterator iterador = aviones.begin(); iterador != aviones.end(); ++iterador){
        Avion* avion = *iterador;
        Decodificador::pushInicial(codigo, avion);
    }
    list<Elemento*> elementos = escenarioJuego->getElementos();
    Decodificador::pushCantidad(codigo, (int) elementos.size());
    for(list<Elemento*>::iterator iterador = elementos.begin(); iterador != elementos.end(); ++iterador){
        Elemento* elemento = *iterador;
        Decodificador::pushInicial(codigo, elemento);
    }
    Decodificador::pushInicialDisparo(codigo, aviones.front()->getIdSpriteDisparos());
    return codigo;
}

string Decodificador::getCodigoEstadoActual(EscenarioJuego *escenarioJuego) {
    string codigo;
    Decodificador::push(codigo, escenarioJuego);
    list<Avion*> aviones = escenarioJuego->getAviones();
    for(list<Avion*>::iterator iterador = aviones.begin(); iterador != aviones.end(); ++iterador){
        Avion* avion = *iterador;
        Decodificador::push(codigo, avion);
    }
    list<Elemento*> elementos = escenarioJuego->getElementos();
    for(list<Elemento*>::iterator iterador = elementos.begin(); iterador != elementos.end(); ++iterador){
        Elemento* elemento = *iterador;
        Decodificador::push(codigo, elemento);
    }
    list<Disparo*> disparos = escenarioJuego->getDisparos();
    Decodificador::pushCantidad(codigo,  (int) disparos.size());
    for(list<Disparo*>::iterator iterador = disparos.begin(); iterador != disparos.end(); ++iterador){
        Disparo* disparo = *iterador;
        Decodificador::push(codigo, disparo);
    }
    return codigo;
}

float Decodificador::popFloat(string & codigo) {
    return stringToFloat(popBytes(codigo, sizeof(float)));
}

int Decodificador::popInt(string & codigo) {
    return stringToInt(popBytes(codigo, sizeof(int)));
}
