#include "decodificador.hpp"
#include <iostream>

/* Push y pop de Strings de ids de sprites e imágenes */

void Decodificador::push(string &codigo, string idImg) {
    push(codigo, (int) idImg.length());
    codigo += idImg;
}

string Decodificador::popIdImg(string &codigo) {
    string lengthString = popBytes(codigo, sizeof(int));
    int length = stringToInt(lengthString);
    return popBytes(codigo, length);
}

/* Push y pop de Elementos del mapa. */
void Decodificador::push(string & codigo, Elemento *e) {
    push(codigo, e->getPosX());
    push(codigo, e->getPosY());
}

string Decodificador::popElemento(string & codigo) {
    return popBytes(codigo, 2 * sizeof(float));
}

/* Push y pop de Aviones. */
void Decodificador::push(string & codigo, Avion* a) {
    push(codigo, a->getPosicionX());
    push(codigo, a->getPosicionY());
    push(codigo, (char) a->getEstadoAnimacion());
}

string Decodificador::popAvion(string & codigo){
    return popBytes(codigo, 2*sizeof(float) + 1);
}

/* Push y pop de disparo. */
void Decodificador::push(string & codigo, Disparo *d) {
    push(codigo, d->getPosX());
    push(codigo, d->getPosY());
}

string Decodificador::popDisparo(string & codigo) {
    return popBytes(codigo, 2*sizeof(float));
}

/* Push enemigo */

void Decodificador::push(string & codigo, AvionEnemigo *enemigo){
    push(codigo, enemigo->getPosicionX());
    push(codigo, enemigo->getPosicionY());
    push(codigo, enemigo->getEstadoAnimacion());
    push(codigo, enemigo->getTipoAvion());
}

/* Push y Pop del Escenario. */
void Decodificador::push(string & codigo, EscenarioJuego *e) {
    push(codigo, e->getScrollingOffset());
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
    for (unsigned int i = 0; i < codigo.length(); ++i) {
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
    push(codigo, e->getAnchoVentana());
    push(codigo, e->getAltoVentana());
    push(codigo, e->getAncho());
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
    string str1 = popBytes(codigo, sizeof(float));
    string str2 = popBytes(codigo, sizeof(float));
    string str3 = popIdImg(codigo);
    return str1 + str2 + str3;
}

string Decodificador::popElementoInicial(string & codigo){
    string str1 = popBytes(codigo, 2*sizeof(float));
    string str2 = popIdImg(codigo);
    return str1 + str2;
}

string Decodificador::popEscenarioInicial(string & codigo){
    string str1 = popBytes(codigo, 2*sizeof(int));
    string str2 = popIdImg(codigo);
    return str1 + str2;
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
    // TODO por ahí no conviene copia sino referencia, por velocidad. Igual es una vez.
    list<Etapa *> etapas = escenarioJuego->getEtapas();
    list<Etapa *>::iterator itEtapa;
    Decodificador::pushCantidad(codigo, etapas.size());
    for (itEtapa = etapas.begin(); itEtapa != etapas.end(); ++itEtapa) {
        list<Elemento*> elementos = (*itEtapa)->getElementos();
        Decodificador::pushCantidad(codigo, elementos.size());
        list<Elemento *>::iterator itElemento;
        for(itElemento = elementos.begin(); itElemento != elementos.end(); ++itElemento) {
            Elemento* elemento = *itElemento;
            Decodificador::pushInicial(codigo, elemento);
        }
    }
    Decodificador::pushInicialDisparo(codigo, aviones.front()->getIdSpriteDisparos());
    return codigo;
}

string Decodificador::getCodigoEstadoActual(EscenarioJuego *escenarioJuego) {
    string codigo;
    Decodificador::push(codigo, escenarioJuego);
    list<Avion*> aviones = escenarioJuego->getAviones();
    for(list<Avion*>::iterator iterador = aviones.begin(); iterador != aviones.end(); ++iterador) {
        Avion* avion = *iterador;
        Decodificador::push(codigo, avion);
    }
    list<Elemento*> elementos = escenarioJuego->getElementos();
    for(list<Elemento*>::iterator iterador = elementos.begin(); iterador != elementos.end(); ++iterador) {
        Elemento* elemento = *iterador;
        Decodificador::push(codigo, elemento);
    }
    list<Disparo*> disparos = escenarioJuego->getDisparos();
    Decodificador::pushCantidad(codigo, (int) disparos.size());
    if(!disparos.empty()){
        for(list<Disparo*>::iterator iterador = disparos.begin(); iterador != disparos.end(); ++iterador) {
            Disparo* disparo = *iterador;
            Decodificador::push(codigo, disparo);
        }
    }
    list<AvionEnemigo*> enemigos = escenarioJuego->getEnemigos();
    Decodificador::pushCantidad(codigo, (int) enemigos.size());
    if(!enemigos.empty()){
        for(list<AvionEnemigo*>::iterator iterador = enemigos.begin(); iterador != enemigos.end(); ++iterador) {
            AvionEnemigo* enemigo = *iterador;
            Decodificador::push(codigo, enemigo);
        }
    }
    return codigo;
}

float Decodificador::popFloat(string & codigo) {
    return stringToFloat(popBytes(codigo, sizeof(float)));
}

int Decodificador::popInt(string & codigo) {
    return stringToInt(popBytes(codigo, sizeof(int)));
}

int Decodificador::popByte(string & codigo) {
    return (int) popBytes(codigo, 1)[0];
}
