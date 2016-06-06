#include "fabricaPowerUps.hpp"

using namespace std;


FabricaPowerUps::FabricaPowerUps() { }

FabricaPowerUps::~FabricaPowerUps() { }

float FabricaPowerUps::generarPosicionX(int anchoEscenario) {
    int anchuraPosible = anchoEscenario - ANCHO_POWERUP;
    int posicionX = rand() % anchuraPosible + 1;

    return posicionX;
}

float FabricaPowerUps::generarPosicionY(int altoEscenario) {
    int alturaPosible = altoEscenario - ALTO_POWERUP;
    int posicionY = rand() % alturaPosible + 1;

    return posicionY;
}

list <PowerUp*> FabricaPowerUps::fabricarPowerUps(list<PowerUpParseado*> powerUpsParseados,int longitudEscenario, int anchoEscenario, int altoEscenario) {

    srand ((unsigned int)time(NULL));

    list <PowerUp*> listaPowerUps;

    for (list<PowerUpParseado*>::iterator itPowerUpsParseados = powerUpsParseados.begin(); itPowerUpsParseados != powerUpsParseados.end(); itPowerUpsParseados++) {
        int tipo = (*itPowerUpsParseados)->getTipo();
        int cantidad = (*itPowerUpsParseados)->getCantidad();
        int valor = (*itPowerUpsParseados)->getValor();

        cout << "se toma un elemento de tipo " << tipo << " y cantidad " << cantidad << endl;
        for(int i = 0; i < cantidad; i++){
          float posicionX = generarPosicionX( anchoEscenario);
          float posicionY = generarPosicionY( altoEscenario);

          if (tipo == TIPO_POWERUP_BONIFICACION){
            generarPowerUpBonificacion(valor, posicionX, posicionY, listaPowerUps);
          } else if (tipo == TIPO_POWERUP_DESTRUIR_ENEMIGOS){
            generarPowerUpDestruirEnemigos(valor, posicionX, posicionY, listaPowerUps);
          } else if(tipo == TIPO_POWERUP_DOS_AMETRALLADORAS){
            generarPowerUpDosAmetralladoras(valor, posicionX, posicionY, listaPowerUps);
          } else if (tipo == TIPO_POWERUP_AVIONES_SECUNDARIOS){
            generarPowerUpAvionesSecundarios(valor, posicionX, posicionY, listaPowerUps);
          }
        }
    }

    return listaPowerUps;
}

void FabricaPowerUps::generarPowerUpBonificacion(float posicionX, float posicionY, int valor, list<PowerUp*>&listaPowerUps){
  PowerUp* powerUp = new PowerUpBonificacion(valor,posicionX,posicionY);
  listaPowerUps.push_back(powerUp);
}

void FabricaPowerUps::generarPowerUpDestruirEnemigos(float posicionX, float posicionY, int valor, list<PowerUp*>&listaPowerUps){
  PowerUp* powerUp = new PowerUpDestruirEnemigos(valor,posicionX,posicionY);
  listaPowerUps.push_back(powerUp);
}

void FabricaPowerUps::generarPowerUpDosAmetralladoras(float posicionX, float posicionY, int valor, list<PowerUp*>&listaPowerUps){
  PowerUp* powerUp = new PowerUpDosAmetralladoras(valor,posicionX,posicionY);
  listaPowerUps.push_back(powerUp);
}

void FabricaPowerUps::generarPowerUpAvionesSecundarios(float posicionX, float posicionY, int valor, list<PowerUp*>&listaPowerUps){
  PowerUp* powerUp = new PowerUpAvionesSecundarios(valor,posicionX,posicionY);
  listaPowerUps.push_back(powerUp);
}
