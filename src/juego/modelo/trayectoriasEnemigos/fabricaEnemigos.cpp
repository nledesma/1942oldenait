#include "fabricaEnemigos.hpp"
#include "trayectoriaRandom.hpp"
#include "trayectoriaIdaYvuelta.hpp"
#include "trayectoriaRulo.hpp"

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

    list< pair<float , AvionEnemigo*> > listaEnemigos; /* Lista con todos los enemigos */

    /* Inicializacion enemigos pequeños */
    if (cantidadPequenios > 0) {
        vector<float> triggersPequenios = this->obtenerTriggerRandom(cantidadPequenios, longitudEscenario);
        for (int i = 0; i < cantidadPequenios; i++) {
            float posXavion = 0;
            float posYavion = 0;
            float angulo = 0;
            int lado = this->obtenerLado();
            if (lado == IZQUIERDA) {
                posXavion = 0;
            } else if (lado == DERECHA) {
                posXavion = anchoEscenario - ANCHO_ENEMIGO_PEQUENIO;
            } else if (lado == ARRIBA) {
                posYavion = 0;
            }

            if (lado != ARRIBA) {
                posYavion = obtenerPosYRandom(altoEscenario, ALTO_ENEMIGO_PEQUENIO);
            } else {
                posXavion = obtenerPosXRandom(anchoEscenario, ANCHO_ENEMIGO_PEQUENIO);
            }

            angulo = this->obtenerAnguloRandom(lado, posXavion, posYavion, anchoEscenario, altoEscenario);

            Trayectoria *trayectoria;
            int randomTrayectoria = rand() % 5;
            if (randomTrayectoria == 0){
                trayectoria = new TrayectoriaRandom();
            } else if (randomTrayectoria == 1){
                trayectoria = new TrayectoriaCuadrada();
            } else {
                trayectoria = new TrayectoriaIdaYvuelta();
                posXavion = obtenerPosXRandom(anchoEscenario, ANCHO_ENEMIGO_PEQUENIO);
                posYavion = 0;
                int randomAngulo = rand() % 2;
                if (randomAngulo == 0){
                    angulo = 270 - 22.5f;
                } else if (randomAngulo == 1){
                    angulo = 270;
                } else {
                    angulo = 270 + 22.5f;
                }
            }
            AvionEnemigo *enemigo = new AvionPequenio(posXavion, posYavion, 200.f, angulo, 200.f, trayectoria);
            float trigger = triggersPequenios[i];

            pair<float, AvionEnemigo *> parTriggerEnemigo;
            parTriggerEnemigo.first = trigger;
            parTriggerEnemigo.second = enemigo;
            listaEnemigos.push_back(parTriggerEnemigo);
        }
    }

    /* Inicialización escuadrones. */
    if (cantidadEscuadrones > 0) {
        vector<float> triggersEscuadrones = this->obtenerTriggerRandom(cantidadEscuadrones, longitudEscenario);
        for (int i = 0; i < cantidadEscuadrones; i++) {
            float posXavion = 0;
            float posYavion = 0;
            float angulo = 0;
            int lado = this->obtenerLado();
            if (lado == IZQUIERDA) {
                posXavion = 0;
            } else if (lado == DERECHA) {
                posXavion = anchoEscenario - ANCHO_ENEMIGO_PEQUENIO;
            } else if (lado == ARRIBA) {
                posYavion = 0;
            }

            if (lado != ARRIBA) {
                posYavion = obtenerPosYRandom(altoEscenario, ALTO_ENEMIGO_PEQUENIO);
            } else {
                posXavion = obtenerPosXRandom(anchoEscenario, ANCHO_ENEMIGO_PEQUENIO);
            }

            angulo = this->obtenerAnguloRandom(lado, posXavion, posYavion, anchoEscenario, altoEscenario);

            Trayectoria *trayectoria1;
            Trayectoria *trayectoria2;
            Trayectoria *trayectoria3;
            Trayectoria *trayectoria4;
            Trayectoria *trayectoria5;

            int trayectoriaRandom = rand() % 2;

            if (trayectoriaRandom == 0){
                trayectoria1 = new TrayectoriaCuadrada();
                trayectoria2 = new TrayectoriaCuadrada();
                trayectoria3 = new TrayectoriaCuadrada();
                trayectoria4 = new TrayectoriaCuadrada();
                trayectoria5 = new TrayectoriaCuadrada();
            } else {
                trayectoria1 = new TrayectoriaRulo();
                trayectoria2 = new TrayectoriaRulo();
                trayectoria3 = new TrayectoriaRulo();
                trayectoria4 = new TrayectoriaRulo();
                trayectoria5 = new TrayectoriaRulo();
            }
            AvionEnemigo *enemigo = new AvionDeEscuadron(posXavion, posYavion, 200.f, angulo, 200.f, trayectoria1);
            float trigger = triggersEscuadrones[i];
            pair<float, AvionEnemigo *> parTriggerEnemigo;
            parTriggerEnemigo.first = trigger;
            parTriggerEnemigo.second = enemigo;
            listaEnemigos.push_back(parTriggerEnemigo);

            enemigo = new AvionDeEscuadron(posXavion, posYavion, 200.f, angulo, 200.f, trayectoria2);
            trigger = trigger + 100;
            parTriggerEnemigo.first = trigger;
            parTriggerEnemigo.second = enemigo;
            listaEnemigos.push_back(parTriggerEnemigo);

            enemigo = new AvionDeEscuadron(posXavion, posYavion, 200.f, angulo, 200.f, trayectoria3);
            trigger = trigger + 100;
            parTriggerEnemigo.first = trigger;
            parTriggerEnemigo.second = enemigo;
            listaEnemigos.push_back(parTriggerEnemigo);

            enemigo = new AvionDeEscuadron(posXavion, posYavion, 200.f, angulo, 200.f, trayectoria4);
            trigger = trigger + 100;
            parTriggerEnemigo.first = trigger;
            parTriggerEnemigo.second = enemigo;
            listaEnemigos.push_back(parTriggerEnemigo);

            enemigo = new AvionDeEscuadron(posXavion, posYavion, 200.f, angulo, 200.f, trayectoria5);
            trigger = trigger + 100;
            parTriggerEnemigo.first = trigger;
            parTriggerEnemigo.second = enemigo;
            listaEnemigos.push_back(parTriggerEnemigo);
        }
    }

    /* Inicialización enemigos medianos. */
    if (cantidadMedianos>0) {
        vector<float> triggersMedianos = this->obtenerTriggerRandom(cantidadMedianos, longitudEscenario);
        for (int i = 0; i < cantidadMedianos; i++) {
            float posXavion = 0;
            float posYavion = 0;
            float angulo = 0;
            int lado = this->obtenerLado();
            if (lado == IZQUIERDA) {
                posXavion = 0;
            } else if (lado == DERECHA) {
                posXavion = anchoEscenario - ANCHO_ENEMIGO_MEDIANO;
            } else if (lado == ARRIBA) {
                posYavion = 0;
            }

            if (lado != ARRIBA) {
                posYavion = obtenerPosYRandom(altoEscenario, ALTO_ENEMIGO_MEDIANO);
            } else {
                posXavion = obtenerPosXRandom(anchoEscenario, ANCHO_ENEMIGO_MEDIANO);
            }

            angulo = this->obtenerAnguloRandom(lado, posXavion, posYavion, anchoEscenario, altoEscenario);

            Trayectoria *trayectoriaRandom = new TrayectoriaRandom();
            AvionEnemigo *enemigo = new AvionMediano(posXavion, posYavion, 160.f, angulo, 200.f, trayectoriaRandom);
            float trigger = triggersMedianos[i];

            pair<float, AvionEnemigo *> parTriggerEnemigo;
            parTriggerEnemigo.first = trigger;
            parTriggerEnemigo.second = enemigo;
            listaEnemigos.push_back(parTriggerEnemigo);
        }
    }

    /* Inicializacion enemigos grandes. */
    if (cantidadGrandes>0) {
        vector<float> triggersGrandes = this->obtenerTriggerRandom(cantidadGrandes, longitudEscenario);
        for (int i = 0; i < cantidadGrandes; i++) {
            float posXavion = obtenerPosXRandom(anchoEscenario, ANCHO_ENEMIGO_GRANDE);
            float posYavion = 800;
            float angulo = 90;

            Trayectoria *trayAvionGrande = new TrayectoriaAvionGrande();
            AvionEnemigo *enemigo = new AvionGrande(posXavion, posYavion, 100.f, angulo, 200.f, trayAvionGrande);
            float trigger = triggersGrandes[i];

            pair<float, AvionEnemigo *> parTriggerEnemigo;
            parTriggerEnemigo.first = trigger;
            parTriggerEnemigo.second = enemigo;
            listaEnemigos.push_back(parTriggerEnemigo);
        }
    }

    listaEnemigos.sort(pairCompare);

    return listaEnemigos;
}


