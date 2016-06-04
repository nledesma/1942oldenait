#include "fabricaEnemigos.hpp"
#include "trayectoriaCuadrada.hpp"

using namespace std;


FabricaEnemigos::FabricaEnemigos() { }

FabricaEnemigos::~FabricaEnemigos() { }

vector<float> FabricaEnemigos::obtenerTriggerRandom(int cantidadPosiciones, int longitudEscenario) {
    vector<float> posiciones;
    int longitudPorcion = (int) floor(longitudEscenario / cantidadPosiciones);

    for (int i = 0; i < cantidadPosiciones; i++){
        int posicionEtapa = rand() % longitudPorcion + 1;

        float posicionAbsoluta = i * longitudPorcion + posicionEtapa;

        posiciones.push_back(posicionAbsoluta);
    }

    return posiciones;
}

float FabricaEnemigos::obtenerPosXRandom(int anchoEscenario, int anchoAvion) {
    int anchoRango = anchoEscenario - anchoAvion;

    int posX = rand() % anchoRango + 1;

    return posX;
}

float FabricaEnemigos::obtenerPosYRandom(int altoEscenario, int altoAvion) {
    int altoRango = altoEscenario - altoAvion;

    int posY = rand() % altoRango + 1;

    return posY;
}

float FabricaEnemigos::obtenerAnguloRandom(int lado, float posX, float posY, int anchoEscenario, int altoEscenario){
    float angulo;
    int randAngle = rand() % 3;

    if (lado == IZQUIERDA){ // Caso izquierda
        if (randAngle == 0)
            angulo = 0;
        else if (randAngle == 1)
            angulo = 22.5;
        else
            angulo = 337.5;
    } else if (lado == DERECHA){ // Caso derecha
        angulo = 157.5f + randAngle * 22.5f;
    } else { // Caso arriba
        angulo = 247.5f + randAngle * 22.5f;
    }
    return angulo;
}

int FabricaEnemigos::obtenerLado() {
    int lado = rand() % 3 + 1;

    if (lado == 1)
        return IZQUIERDA;
    else if (lado == 2)
        return DERECHA;
    else
        return ARRIBA;
}

bool pairCompare(const std::pair<float, AvionEnemigo*>& firstElem, const std::pair<float, AvionEnemigo*>& secondElem) {
    return firstElem.first < secondElem.first;

}

list< pair<float , AvionEnemigo*> > FabricaEnemigos::fabricarEnemigos(int cantidadPequenios, int cantidadEscuadrones,
                                                      int cantidadMedianos, int cantidadGrandes,
                                                      int longitudEscenario, int anchoEscenario, int altoEscenario) {
    srand ((unsigned int)time(NULL));

    list< pair<float , AvionEnemigo*> > listaEnemigos;

    vector<float> posicionesPequenios = this->obtenerTriggerRandom(cantidadPequenios, longitudEscenario);
    for (int i = 0; i < cantidadPequenios; i ++){
        float posXavion = 0;
        float posYavion = 0;
        float angulo = 0;
        int lado = this->obtenerLado();
        if (lado == IZQUIERDA) {
            posXavion = 0;
        } else if (lado == DERECHA) {
            posXavion = anchoEscenario - ANCHO_ENEMIGO_PEQUENIO;
        } else if (lado == ARRIBA){
            posYavion = 0;
        }

        if (lado != ARRIBA){
            posYavion = obtenerPosYRandom( altoEscenario, ALTO_ENEMIGO_PEQUENIO);
        } else {
            posXavion = obtenerPosXRandom( anchoEscenario, ANCHO_ENEMIGO_PEQUENIO);
        }

        angulo = this->obtenerAnguloRandom(lado, posXavion, posYavion, anchoEscenario, altoEscenario);

        Trayectoria* cuadrada = new TrayectoriaCuadrada();
        AvionEnemigo* enemigo = new AvionPequenio(posXavion, posYavion, 200.f, angulo, 200.f, cuadrada);
        float trigger = posicionesPequenios[i];

        pair <float, AvionEnemigo*> parTriggerEnemigo;
        parTriggerEnemigo.first = trigger;
        parTriggerEnemigo.second = enemigo;
        listaEnemigos.push_back(parTriggerEnemigo);
    }

    vector<float> posicionesMedianos = this->obtenerTriggerRandom(cantidadMedianos, longitudEscenario);
    for (int i = 0; i < cantidadMedianos; i ++){
        float posXavion = 0;
        float posYavion = 0;
        float angulo = 0;
        int lado = this->obtenerLado();
        if (lado == IZQUIERDA) {
            posXavion = 0;
        } else if (lado == DERECHA) {
            posXavion = anchoEscenario - ANCHO_ENEMIGO_MEDIANO;
        } else if (lado == ARRIBA){
            posYavion = 0;
        }

        if (lado != ARRIBA){
            posYavion = obtenerPosYRandom( altoEscenario, ALTO_ENEMIGO_MEDIANO);
        } else {
            posXavion = obtenerPosXRandom( anchoEscenario, ANCHO_ENEMIGO_MEDIANO);
        }

        angulo = this->obtenerAnguloRandom(lado, posXavion, posYavion, anchoEscenario, altoEscenario);

        Trayectoria* cuadrada = new TrayectoriaCuadrada();
        AvionEnemigo* enemigo = new AvionMediano(posXavion, posYavion, 200.f, angulo, 200.f, cuadrada);
        float trigger = posicionesMedianos[i];

        pair <float, AvionEnemigo*> parTriggerEnemigo;
        parTriggerEnemigo.first = trigger;
        parTriggerEnemigo.second = enemigo;
        listaEnemigos.push_back(parTriggerEnemigo);
    }

    listaEnemigos.sort(pairCompare);

    return listaEnemigos;
}


