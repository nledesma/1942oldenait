#include "avionGrande.hpp"

AvionGrande::AvionGrande(float posX, float posY, float velocidad, float angulo, float velocidadDisparos, Trayectoria* trayectoria){
    this->posX = posX;
    this->posY = posY;
    this->angulo = angulo;
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->estadoAnimacion = AVION_ENEMIGO_GRANDE_NORMAL;
    this->idSprite = SPRITE_AVION_ENEMIGO_GRANDE;
    this->idSpriteDisparos = SPRITE_DISPARO_ENEMIGO;
    this->trayectoria = trayectoria;
    this->colisionable = new Colisionable(this->posX, this->posY, angulo, TIPO_AVION_GRANDE);
    this->tipoAvion = TIPO_AVION_GRANDE;
}

AvionGrande::~AvionGrande(){

}

int AvionGrande::getAncho() {
    return ANCHO_ENEMIGO_GRANDE;
}

int AvionGrande::getAlto() {
    return ALTO_ENEMIGO_GRANDE;
}

bool AvionGrande::correspondeDisparar(float timestep) {
    if ((this->contadorTimesteps + timestep) >= FRECUENCIA_DISPAROS){
        this->contadorTimesteps = 0;
        return (this->getPosicionY() <= ALTURA_INICIO_DISPAROS);
    }
    this->contadorTimesteps += timestep;
    return false;
}

vector<DisparoEnemigo*> AvionGrande::disparar(){

    vector <DisparoEnemigo*> disparos;
    float xObjetivo = 0;
    float yObjetivo = ALTO_ESCENARIO;
    float difX = (float) pow(xObjetivo - this->posX, 2);
    float difY = (float) pow(yObjetivo - this->posY, 2);
    float norma = (float) sqrt(difX + difY);

    float versorX = (xObjetivo - this->posX) / norma;
    float versorY = (yObjetivo - this->posY) / norma;

    float posInicialX = this->posX + this->getAncho() /2.f - ANCHO_DISPARO_ENEMIGO / 2.f;
    float posInicialY = this->posY + this->getAlto() / 2.f - ALTO_DISPARO_ENEMIGO / 2.f;
    DisparoEnemigo* disparo1 = new DisparoEnemigo(posInicialX, posInicialY, 200, versorX, versorY);
    disparos.push_back(disparo1);

    xObjetivo = ANCHO_ESCENARIO / 2.f;
    yObjetivo = ALTO_ESCENARIO;
    difX = (float) pow(xObjetivo - this->posX, 2);
    difY = (float) pow(yObjetivo - this->posY, 2);
    norma = (float) sqrt(difX + difY);

    versorX = (xObjetivo - this->posX) / norma;
    versorY = (yObjetivo - this->posY) / norma;

    posInicialX = this->posX + this->getAncho() /2.f - ANCHO_DISPARO_ENEMIGO / 2.f;
    posInicialY = this->posY + this->getAlto() / 2.f - ALTO_DISPARO_ENEMIGO / 2.f;
    DisparoEnemigo* disparo2 = new DisparoEnemigo(posInicialX, posInicialY, 200, versorX, versorY);
    disparos.push_back(disparo2);

    xObjetivo = ANCHO_ESCENARIO;
    yObjetivo = ALTO_ESCENARIO;
    difX = (float) pow(xObjetivo - this->posX, 2);
    difY = (float) pow(yObjetivo - this->posY, 2);
    norma = (float) sqrt(difX + difY);

    versorX = (xObjetivo - this->posX) / norma;
    versorY = (yObjetivo - this->posY) / norma;

    posInicialX = this->posX + this->getAncho() /2.f - ANCHO_DISPARO_ENEMIGO / 2.f;
    posInicialY = this->posY + this->getAlto() / 2.f - ALTO_DISPARO_ENEMIGO / 2.f;
    DisparoEnemigo* disparo3 = new DisparoEnemigo(posInicialX, posInicialY, 200, versorX, versorY);
    disparos.push_back(disparo3);

    return disparos;
}