#ifndef DECO_H
#define DECO_H

#include "../juego/modelo/elemento.hpp"
#include "../juego/modelo/avion.hpp"
#include "../juego/modelo/escenarioJuego.hpp"
#include "../juego/modelo/disparo.hpp"
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
    static void push (string & codigo, string idImg);
    static void push(string & codigo, Elemento *e);
    static void push(string & codigo, Avion *a);
    static void push(string & codigo, Disparo *d);
    static void push(string & codigo, EscenarioJuego *e);
    static void pushInicial(string & codigo, Avion *a);
    static void pushInicial(string & codigo, Elemento *e);
    static void pushInicial(string & codigo, EscenarioJuego *e);
    static void pushInicialDisparo(string & codigo, string idSpriteDisparo);
    /* Devuelve un par con el id y el código con el nuevo estado */
    static string popIdImg(string & codigo);
    static string popElemento(string & codigo);
    static string popAvion(string & codigo);
    static string popEscenario(string & codigo);
    static string popDisparo(string & codigo);
    static void imprimirBytes(string codigo);
};

#endif
