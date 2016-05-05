#ifndef DECO_H
#define DECO_H

#include "../juego/modelo/elemento.hpp"
#include "../juego/vista/elementoVista.hpp"
#include "../accesorios/codigo.hpp"
#include <utility> // pair
#include <cstring> // memcpy
using namespace std;

class Decodificador {
private:
    /* Se le da una variable y agrega sus bytes a la string. */
    template<typename T> static void push(string & str, T e);
    static string popBytes(string & codigo, int cBytes);
public:
    static void push(string & str, Elemento *e);
    static Elemento * decodificar(string e);
    static void imprimirBytes(string codigo);
    /* Devuelve un par con el id y el código con el nuevo estado */
    static pair<int,string> popElemento(string & codigo);
};

#endif
