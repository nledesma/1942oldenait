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
    this->vidas = 10;
    this->valorImpacto = 100;
    this->valorDerribo = 1000;
}

AvionGrande::~AvionGrande(){

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

    float posInicialX = this->posX + ANCHO_ENEMIGO_GRANDE /2.f - ANCHO_DISPARO_ENEMIGO / 2.f;
    float posInicialY = this->posY + ALTO_ENEMIGO_GRANDE / 2.f - ALTO_DISPARO_ENEMIGO / 2.f;
    DisparoEnemigo* disparo1 = new DisparoEnemigo(posInicialX, posInicialY, 200, versorX, versorY);
    disparos.push_back(disparo1);

    xObjetivo = ANCHO_ESCENARIO / 2.f;
    yObjetivo = ALTO_ESCENARIO;
    difX = (float) pow(xObjetivo - this->posX, 2);
    difY = (float) pow(yObjetivo - this->posY, 2);
    norma = (float) sqrt(difX + difY);

    versorX = (xObjetivo - this->posX) / norma;
    versorY = (yObjetivo - this->posY) / norma;

    DisparoEnemigo* disparo2 = new DisparoEnemigo(posInicialX, posInicialY, 200, versorX, versorY);
    disparos.push_back(disparo2);

    xObjetivo = ANCHO_ESCENARIO;
    yObjetivo = ALTO_ESCENARIO;
    difX = (float) pow(xObjetivo - this->posX, 2);
    difY = (float) pow(yObjetivo - this->posY, 2);
    norma = (float) sqrt(difX + difY);

    versorX = (xObjetivo - this->posX) / norma;
    versorY = (yObjetivo - this->posY) / norma;

    DisparoEnemigo* disparo3 = new DisparoEnemigo(posInicialX, posInicialY, 200, versorX, versorY);
    disparos.push_back(disparo3);

    return disparos;
}

void AvionGrande::colisionar(){
    this->vidas -= 1;
    if (this->vidas == 0) {
        if (this->estadoAnimacion < AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1) {
            this->estadoAnimacion = AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1;
        }
    } else if (this->vidas == 7) {
        this->estadoAnimacion = AVION_ENEMIGO_GRANDE_DANIADO_1;
    } else if (this->vidas == 3) {
        this->estadoAnimacion = AVION_ENEMIGO_GRANDE_DANIADO_2;
    }
}

int AvionGrande::mover(float timeStep) {
    pthread_mutex_lock(&this->mutexMover);
    int sigueEnPantalla = 1;
    if(this->estadoAnimacion < AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1){
        this->trayectoria->mover(this->posX, this->posY, this->velocidad, this->angulo, this->estadoAnimacion, timeStep);
        // TODO: chequear los bordes usando los atributos del escenario
        if (this->posX > ANCHO_ESCENARIO || this->posX < - this->getAncho()
            || this->posY > ALTO_ESCENARIO || this->posY < - this->getAlto()){
            sigueEnPantalla = 0;
        }
        this->colisionable->mover(this->posX, this->posY, this->angulo, TIPO_AVION_GRANDE);
    } else {
        if(this->contador > 0 ) {
            this->contador --;
        } else {
            if(this->estadoAnimacion == AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_12){
                sigueEnPantalla = 0;
            } else {
                this->estadoAnimacion ++;
            }
            this->contador = CONTADOR_INICIAL;
        }
    }
    pthread_mutex_unlock(&this->mutexMover);
    return sigueEnPantalla;
}

int AvionGrande::estallar(){
    colisionar();
    return this->valorDerribo;
}
