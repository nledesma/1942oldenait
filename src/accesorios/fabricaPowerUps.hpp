#ifndef INC_1942OLDENAIT_FABRICAPOWERUPS_HPP
#define INC_1942OLDENAIT_FABRICAPOWERUPS_HPP

#include "powerUpParseado.hpp"
#include "../juego/modelo/powerUp.hpp"
#include "../juego/modelo/powerUpBonificacion.hpp"
#include "../juego/modelo/powerUpDestruirEnemigos.hpp"
#include "../juego/modelo/powerUpDosAmetralladoras.hpp"
#include "../juego/modelo/powerUpAvionesSecundarios.hpp"
#include "codigo.hpp"
#include "default.hpp"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class FabricaPowerUps {
private:
    float generarPosicionX(int anchoEscenario);
    float generarPosicionY(int altoEscenario);
public:
    FabricaPowerUps();
    ~FabricaPowerUps();
    list<PowerUp*> fabricarPowerUps(list<PowerUpParseado*> powerUpsParseados,int longitudEscenario,int anchoEscenario,int altoEscenario);
    void generarPowerUpBonificacion(float posicionX, float posicionY, int valor, list<PowerUp*> &listaPowerUps);
    void generarPowerUpDestruirEnemigos(float posicionX, float posicionY, int valor, list<PowerUp*> &listaPowerUps);
    void generarPowerUpDosAmetralladoras(float posicionX, float posicionY, int valor, list<PowerUp*> &listaPowerUps);
    void generarPowerUpAvionesSecundarios(float posicionX, float posicionY, int valor, list<PowerUp*> &listaPowerUps);
};

#endif //INC_1942OLDENAIT_FABRICAPOWERUPS_HPP
