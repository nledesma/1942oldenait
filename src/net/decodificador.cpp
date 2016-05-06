#include "decodificador.hpp"
#include <iostream>


/* Push y pop de Elementos del mapa. */
void Decodificador::push(string & codigo, Elemento *e){
    // id (1 byte) | pos_x (1 float) | pos_y (1 float)
    codigo += (char)(e->getId());
    push(codigo, e->getPosX());
    push(codigo, e->getPosY());
}

pair<int,string> Decodificador::popElemento(string & codigo){
    pair<int,string> idCodigo;
    string aux = popBytes(codigo, 2 * sizeof(float) + 1);
    idCodigo.first = (int) aux[0];
    idCodigo.second = aux.substr(1, aux.length() - 1);
    return idCodigo;
}

/* Push y pop de Aviones. */
void Decodificador::push(string & codigo, Avion* a, int nroAvion){
    // Nro (1 byte) | posX, posY (2 floats) | estadoAnimacion (1 byte)
    push((char) nroAvion);
    push(codigo, a->getPosicionX());
    push(codigo, a->getPosicionY());
    push(codigo, (char) a->getEstadoAnimacion());
}

pair<int,string> Decodificador::popAvion(string & codigo){
    pair<int,string> idCodigo;
    string aux = popBytes(codigo, 2*sizeof(float) + 2);
    idCodigo.first = (int) aux[0];
    idCodigo.second = aux.substr(1, aux.length() - 1);
    return idCodigo;
}

/* Generales para cualquier tipo */
template<typename T> void Decodificador::push(string & str, T e){
    int n = sizeof(e);
    char * bytes = new char[n];
    memcpy((void*)bytes, (void*) &e, n);

    for (int i = 0; i < n; i++) {
        str += bytes[i];
    }

    delete bytes;
}

string Decodificador::popBytes(string & codigo, int cBytes){
    string ret = codigo.substr(0, cBytes);
    codigo.erase(0, cBytes);
    return ret;
}

void Decodificador::imprimirBytes(string codigo){
    for (int i = 0; i < codigo.length(); ++i){
        cout << (int) codigo[i] << " ";
    }
    cout << endl;
}
