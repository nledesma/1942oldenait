#ifndef INC_1942OLDENAIT_FABRICA_DE_ENEMIGOS_HPP
#define INC_1942OLDENAIT_FABRICA_DE_ENEMIGOS_HPP

#include <algorithm>
#include "../avionEnemigo.hpp"
#include "../avionPequenio.hpp"
#include "../avionDeEscuadron.hpp"
#include "../avionMediano.hpp"
#include "../avionGrande.hpp"
#include "trayectoriaCuadrada.hpp"
#include "trayectoriaAvionGrande.hpp"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define IZQUIERDA 1
#define DERECHA 2
#define ARRIBA 3

using namespace std;

// TODO FALTAN BANDA DE FREES EN ESTE LUGAR JEJEEJEJEJEJE

class FabricaEnemigos {
private:
    vector<float> obtenerTriggerRandom(int cantidadPosiciones, int longitudEscenario);
    int obtenerLado();
    float obtenerPosXRandom(int anchoEscenario, int anchoAvion);
    float obtenerPosYRandom(int altoEscenario, int altoAvion);
    float obtenerAnguloRandom(int lado, float posX, float posY, int anchoEscenario, int altoEscenario);
public:
    FabricaEnemigos();
    ~FabricaEnemigos();
    list< pair<float , AvionEnemigo*> > fabricarEnemigos(int cantidadPequenios, int cantidadEscuadrones,
                                                         int cantidadMedianos, int cantidadGrandes,
                                                         int longitudEscenario, int anchoEscenario, int altoEscenario);
};

#endif //INC_1942OLDENAIT_FABRICA_DE_ENEMIGOS_HPP
