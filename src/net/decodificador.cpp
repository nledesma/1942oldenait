#include "decodificador.hpp"
#include <iostream>

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
