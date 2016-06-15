#ifndef DECO_H
#define DECO_H

#include "../juego/modelo/elemento.hpp"
#include "../juego/modelo/avion.hpp"
#include "../juego/modelo/escenarioJuego.hpp"
#include "../juego/modelo/disparo.hpp"
#include "../juego/modelo/powerUp.hpp"
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
    static void pushEvento(string & codigo, int evento);
    static void push(string & codigo, string idImg);
    static void push(string & codigo, Elemento *e);
    static void push(string & codigo, Avion *a);
    static void push(string & codigo, Disparo *d);
    static void push(string & codigo, DisparoEnemigo *d);
    static void push(string & codigo, AvionEnemigo *enemigo);
    static void push(string & codigo, EscenarioJuego *e);
    static void push(string & codigo, PowerUp *powerUp);
    static void push(string & codigo, bool b);
    static void pushInicial(string & codigo, Avion *a);
    static void pushInicial(string & codigo, Elemento *e);
    static void pushInicial(string & codigo, EscenarioJuego *e);
    static void pushInicialDisparo(string & codigo, string idSpriteDisparo);
    static void pushCantidad(string & codigo, int cantidad);
    /* Devuelve un par con el id y el código con el nuevo estado */
    static string popString(string &codigo);
    static string popElemento(string & codigo);
    static string popAvion(string & codigo);
    static string popEscenario(string & codigo);
    static string popDisparo(string & codigo);
    static string popAvionInicial(string & codigo);
    static string popPowerUpInicial(string &codigo);
    static string popElementoInicial(string & codigo);
    static string popEscenarioInicial(string & codigo);
    static string popDisparoInicial(string & codigo);
    static string popEvento(string & codigo);
    static string popCantidad(string & codigo);
    static bool popBool(string & codigo);
    static float popFloat(string & codigo);
    static int popInt(string & codigo);
    static int popByte(string & codigo);
    static int stringToInt(string codigo);
    static float stringToFloat(string codigo);
    static void imprimirBytes(string codigo);
    static string getCodigoEstadoInicial(EscenarioJuego * escenarioJuego);
    static string getCodigoEstadoActual(EscenarioJuego * escenarioJuego);
    static string getPuntajes(EscenarioJuego * escenarioJuego, map<int, string> nombreSegunNroAvion);
};

#endif
