#include "avion.hpp"

using namespace std;

Avion::Avion(float posX, float posY, float velocidad, float velocidadDisparos, string idSprite, string idSpriteDisparos, int numeroAvion, int vidas, float posXFinal, float posYFinal){
    this->posX = posX;
    this->posY = posY;
    this->posXInicial = posX;
    this->posYInicial = posY;
    this->posXFinal = posXFinal;
    this->posYFinal = posYFinal;
    this->velocidadX = 0;
    this->velocidadY = 0;
    this->colisionable = new Colisionable(posX, posY, 0, TIPO_AVION);
    this->velocidad = velocidad;
    this->velocidadDisparos = velocidadDisparos;
    this->contador = CONTADOR_INICIAL;
    this->estadoAnimacion = ESTADO_NORMAL;
    this->idSprite = idSprite;
    this->idSpriteDisparos = idSpriteDisparos;
    this->puntaje = 0;
    this->vidas = vidas;
    this->numeroAvion = numeroAvion;
    this->estadoPowerUP = ESTADO_SIN_POWER_UP;
    this->cantidadDisparos = 0;
    this->cantidadAciertos = 0;
    this->puntajeAvionesSecundarios = 0;
}

Avion::~Avion(){

}

int Avion::obtenerPuntajesAvionesSecundarios(){
    if(avionesSecundarios.size() != 0){
        for(list<AvionSecundario*>::iterator itAvionesSecundarios = this->avionesSecundarios.begin(); itAvionesSecundarios != this->avionesSecundarios.end(); itAvionesSecundarios++){
            AvionSecundario* avionSecundario = (*itAvionesSecundarios);
            if(avionSecundario->getPuntaje() != 0){
                puntajeAvionesSecundarios += avionSecundario->getPuntaje();
            }
        }
    }
    return puntajeAvionesSecundarios;
}

AvionSecundario* Avion::getAvionSecundario(){
    list<AvionSecundario*>::iterator it = avionesSecundarios.begin();
    advance (it, avionesSecundarios.size() - 1);
    AvionSecundario *avionSecundario = *it;
    return avionSecundario;
}

void Avion::manejarAvionesSecundarios(int evento){
    for(list<AvionSecundario*>::iterator itAvionesSecundarios = this->avionesSecundarios.begin(); itAvionesSecundarios != this->avionesSecundarios.end(); itAvionesSecundarios++){
        AvionSecundario* avionSecundario = (*itAvionesSecundarios);
        avionSecundario->manejarEvento(evento);
    }
}

vector<DisparoAvionSecundario*> Avion::dispararAvionesSecundarios(){
    //TODO aca los disparos se mandan bien.!
    // cout << "ENTRO AL METODO DISPARAR AVIONES SECUNDARIOS DE AVION COMUN" << endl;
    vector<DisparoAvionSecundario*> disparos;
    for(list<AvionSecundario*>::iterator itAvionesSecundarios = this->avionesSecundarios.begin(); itAvionesSecundarios != this->avionesSecundarios.end(); itAvionesSecundarios++){
        AvionSecundario* avionSecundario = (*itAvionesSecundarios);
        // cout << "ESTA POR DISPARAR UN AVION SECUNDARIO" << endl;
        disparos = avionSecundario->disparar();
        // cout << "DISPARO: " << disparo[i] << endl;
    }
    // for(int i = 0; i < disparos.size(); i++){
    //     cout << "DISPARO AVION SECUNDARIO EN X: " << disparos[i]->getPosX() << endl;
    //     cout << "DISPARO AVION SECUNDARIO EN Y: " << disparos[i]->getPosY() << endl;
    // }
    return disparos;
}

void Avion::manejarEvento(int evento){
    /* Se realizan acciones de avión si el mismo no esta loopeando */
    if((this->estadoAnimacion < LOOP_ETAPA_1 || this->estadoAnimacion == INTERMITENCIA) && this->estadoAnimacion != ESTADO_AVION_DESTRUIDO ) {
        switch (evento) {
            case ARRIBA_PRESIONA:
                this->velocidadY -= this->velocidad;
                break;
            case ABAJO_PRESIONA:
                this->velocidadY += this->velocidad;
                break;
            case IZQUIERDA_PRESIONA:
                this->velocidadX -= this->velocidad;
                this->estadoAnimacion = GIRANDO_IZQUIERDA;
                break;
            case DERECHA_PRESIONA:
                this->estadoAnimacion = GIRANDO_DERECHA;
                this->velocidadX += this->velocidad;
                break;
            case PRESIONA_ENTER:
                this->estadoAnimacion = LOOP_ETAPA_1;
                this->estadoAnimacion = this->estadoAnimacion + OFFSET_ESTADO_LOOP;
                break;
            case ARRIBA_SUELTA:
                if (this->velocidadY != 0)
                    this->velocidadY += this->velocidad;
                break;
            case ABAJO_SUELTA:
                if (this->velocidadY != 0)
                    this->velocidadY -= this->velocidad;
                break;
            case IZQUIERDA_SUELTA:
                if (this->velocidadX != 0 || this->estadoAnimacion == GIRANDO_DERECHA || this->estadoAnimacion == INTERMITENCIA)
                    this->velocidadX += this->velocidad;
                if (this->estadoAnimacion != GIRANDO_DERECHA)
                    this->estadoAnimacion = ESTADO_NORMAL;
                break;
            case DERECHA_SUELTA:
                if (this->velocidadX != 0 || this->estadoAnimacion == GIRANDO_IZQUIERDA || this->estadoAnimacion == INTERMITENCIA)
                    this->velocidadX -= this->velocidad;
                if (this->estadoAnimacion != GIRANDO_IZQUIERDA)
                    this->estadoAnimacion = ESTADO_NORMAL;
                break;
        }
    }
}

void Avion::disminuirTiempoInmunidad(float timestep) {
    if (this->contadorTiempoInmunidad > 0) {
        if ((this->contadorTiempoInmunidad - timestep) >= 0) {
            if ((this->contadorIntermitenciaInmunidad - timestep) >= 0) {
                this->contadorIntermitenciaInmunidad -= timestep;
            } else {
                this->contadorIntermitenciaInmunidad = TIEMPO_INTERMITENCIA;
                if (this->estadoAnimacion != INTERMITENCIA) {
                    this->estadoAnimacion = INTERMITENCIA;
                } else {
                    this->estadoAnimacion = ESTADO_NORMAL;
                }
            }
            this->contadorTiempoInmunidad -= timestep;
        } else {
            this->contadorTiempoInmunidad = 0;
            this->estadoAnimacion = ESTADO_NORMAL;
        }
    }
}

void Avion::mover(float timeStep){
    pthread_mutex_lock(&this->mutexMover);
    if(this->estadoAnimacion < EXPLOSION_ETAPA_1 && this->estadoAnimacion != ESTADO_AVION_DESTRUIDO  && ((this->estadoPowerUP == ESTADO_POWER_UP_AVIONES_SECUNDARIOS) || (this->estadoPowerUP == ESTADO_POWER_UP_DOBLE) || (this->avionesSecundarios.size() > 0))){
        this->moverConPowerUP(timeStep);
    } else {
        if (this->estadoAnimacion != ESTADO_AVION_DESTRUIDO) {
            if (this->estadoAnimacion >= OFFSET_ESTADO_DISPARO && this->estadoAnimacion < OFFSET_ESTADO_LOOP) {
                this->estadoAnimacion = this->estadoAnimacion - OFFSET_ESTADO_DISPARO;
            } else if (this->estadoAnimacion >= OFFSET_ESTADO_LOOP && this->estadoAnimacion < OFFSET_ESTADO_EXPLOSION) {
                this->estadoAnimacion = this->estadoAnimacion - OFFSET_ESTADO_LOOP;
            } else if (this->estadoAnimacion >= OFFSET_ESTADO_EXPLOSION) {
                this->estadoAnimacion = this->estadoAnimacion - OFFSET_ESTADO_EXPLOSION;
            }
            if (this->estadoAnimacion < 3 || this->estadoAnimacion == INTERMITENCIA) {
                this->posX += this->velocidadX * timeStep;
                if (this->posX < 0) {
                    this->posX = 0;
                } else if (this->posX + this->getAncho() > ANCHO_ESCENARIO) {
                    this->posX = ANCHO_ESCENARIO - this->getAncho();
                }
                this->posY += this->velocidadY * timeStep;
                if (this->posY < 0) {
                    this->posY = 0;
                } else if (this->posY + this->getAlto() > ALTO_ESCENARIO) {
                    this->posY = ALTO_ESCENARIO - this->getAlto();
                }
                this->colisionable->mover(this->posX, this->posY, 0, TIPO_AVION);
            } else {
                if (this->estadoAnimacion != DESCONECTADO) {
                    if(this->estadoAnimacion >= EXPLOSION_ETAPA_1){
                        this->destruirAvionesSecundarios();
                    }
                    if (this->contador > 0) {
                        this->contador--;
                        if (this->estadoAnimacion >= LOOP_ETAPA_1 && this->estadoAnimacion < LOOP_ETAPA_5) {
                            this->posY -= (this->velocidad / 2.f) * timeStep;
                        } else if (this->estadoAnimacion >= LOOP_ETAPA_7 && this->estadoAnimacion < LOOP_ETAPA_13) {
                            this->posY += (this->velocidad / 2.f) * timeStep;
                        }
                    } else {
                        this->contador = CONTADOR_INICIAL;
                        if (this->estadoAnimacion == LOOP_ETAPA_17) {
                            this->estadoAnimacion = ESTADO_NORMAL;
                        } else if (this->estadoAnimacion == EXPLOSION_ETAPA_10) {
                            this->volverEstadoInicial();
                        } else {
                            this->estadoAnimacion++;
                        }
                    }
                    if (this->estadoAnimacion == LOOP_ETAPA_17) {
                        this->velocidadX = 0;
                        this->velocidadY = 0;
                    }
                }
            }
            this->disminuirTiempoInmunidad(timeStep);
        }
    }
    pthread_mutex_unlock(&this->mutexMover);
}

void Avion::moverConPowerUP(float timeStep){
    int offset = ANCHO_ESCENARIO;
    int cambiarPosicion = 0;
    if(this->posX > ANCHO_ESCENARIO/2){
        offset -= ANCHO_AVION_SECUNDARIO;
        cambiarPosicion = ANCHO_ESCENARIO - ANCHO_AVION_CON_POWER_UP;
        // cout << "CAMBIAR POSICION: " << cambiarPosicion << endl;
    } else {
        // cout << "ENTRO AL LADO IZQUIERDO" << endl;
        offset += ANCHO_AVION_SECUNDARIO;
        cambiarPosicion = ANCHO_AVION_CON_POWER_UP;
        // cout << "CAMBIAR POSICION: " << cambiarPosicion << endl;
    }
    if (this->estadoAnimacion != ESTADO_AVION_DESTRUIDO) {
        if (this->estadoAnimacion >= OFFSET_ESTADO_DISPARO && this->estadoAnimacion < OFFSET_ESTADO_LOOP) {
            this->estadoAnimacion = this->estadoAnimacion - OFFSET_ESTADO_DISPARO;
        } else if (this->estadoAnimacion >= OFFSET_ESTADO_LOOP && this->estadoAnimacion < OFFSET_ESTADO_EXPLOSION) {
            this->estadoAnimacion = this->estadoAnimacion - OFFSET_ESTADO_LOOP;
        } else if (this->estadoAnimacion >= OFFSET_ESTADO_EXPLOSION) {
            this->estadoAnimacion = this->estadoAnimacion - OFFSET_ESTADO_EXPLOSION;
        }
        if (this->estadoAnimacion < 3) {
            this->posX += this->velocidadX * timeStep;
            cout << "POS X: " << this->posX << endl;
            if (this->posX < 0) {
                this->posX = ANCHO_AVION_SECUNDARIO;
            } else if (this->posX + this->getAncho() > offset) {
                cout << "ENTRO AL ELSE IF" << endl;
                this->posX = cambiarPosicion;
                cout << "POS X: " << this->posX << endl;
            }
            this->posY += this->velocidadY * timeStep;
            if (this->posY < 0) {
                this->posY = 0;
            } else if (this->posY + this->getAlto() > ALTO_ESCENARIO) {
                this->posY = ALTO_ESCENARIO - this->getAlto();
            }
            this->colisionable->mover(this->posX, this->posY, 0, TIPO_AVION);
        } else {
            if (this->estadoAnimacion != DESCONECTADO) {
                if (this->contador > 0) {
                    this->contador--;
                    if (this->estadoAnimacion >= LOOP_ETAPA_1 && this->estadoAnimacion < LOOP_ETAPA_5) {
                        this->posY -= (this->velocidad / 2.f) * timeStep;
                    } else if (this->estadoAnimacion >= LOOP_ETAPA_7 && this->estadoAnimacion < LOOP_ETAPA_13) {
                        this->posY += (this->velocidad / 2.f) * timeStep;
                    }
                } else {
                    this->contador = CONTADOR_INICIAL;
                    if (this->estadoAnimacion == LOOP_ETAPA_17) {
                        this->estadoAnimacion = ESTADO_NORMAL;
                    } else if (this->estadoAnimacion == EXPLOSION_ETAPA_10) {
                        this->volverEstadoInicial();
                    } else {
                        this->estadoAnimacion++;
                    }
                }
                if (this->estadoAnimacion == LOOP_ETAPA_17) {
                    this->velocidadX = 0;
                    this->velocidadY = 0;
                }
            }
        }
        this->disminuirTiempoInmunidad(timeStep);
    }
}


void Avion::destruirAvionesSecundarios() {
    for(list<AvionSecundario*>::iterator itAvionesSec = this->avionesSecundarios.begin(); itAvionesSec != this->avionesSecundarios.end(); itAvionesSec++){
        (*itAvionesSec)->setVelocidad(0);
        (*itAvionesSec)->colisionar();
    }
}

float Avion::getVelocidad(){
    return this->velocidad;
}

void Avion::setVelocidad(float velocidad){
    this->velocidad = velocidad;
}

float Avion::getPosicionX(){
    pthread_mutex_lock(&this->mutexMover);
    float posicionX = this->posX;
    pthread_mutex_unlock(&this->mutexMover);
    return posicionX;
}
float Avion::getPosicionY(){
    pthread_mutex_lock(&this->mutexMover);
    float posicionY = this->posY;
    pthread_mutex_unlock(&this->mutexMover);
    return posicionY;}

void Avion::setEstadoAnimacion(int estadoAnimacion){
    pthread_mutex_lock(&this->mutexMover);
    this->estadoAnimacion = estadoAnimacion;
    pthread_mutex_unlock(&this->mutexMover);
}

int Avion::getAncho(){
    return AVION_ANCHO;
}
int Avion::getAlto(){
    return AVION_ALTO;
}

int Avion::getAnchoDisparo(){
    return DISPARO_ANCHO;
}

int Avion::getAltoDisparo(){
    return DISPARO_ALTO;
}

int Avion::getEstadoAnimacion(){
    pthread_mutex_lock(&this->mutexMover);
    int estado = this->estadoAnimacion;
    pthread_mutex_unlock(&this->mutexMover);
    return estado;
}

vector<Disparo*> Avion::disparar(){
    // Por ahora sale con la misma velocidad y posición que el avión.
    vector<Disparo*> disparos;
    if (this->estadoAnimacion != ESTADO_AVION_DESTRUIDO) {
        if (estadoAnimacion > LOOP_ETAPA_1 || this->contadorTiempoInmunidad > 0) {
            return disparos;
        }
        this->estadoAnimacion = this->estadoAnimacion + OFFSET_ESTADO_DISPARO;
        if (this->estadoPowerUP == ESTADO_SIN_POWER_UP) {
            disparos.push_back(new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f,
                                           this->getPosicionY(), velocidadDisparos));
            this->cantidadDisparos+= 1;
        } else if (this->estadoPowerUP == ESTADO_POWER_UP_DISPARO_DOBLE){
            disparos.push_back(
                    new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f - 10,
                                this->getPosicionY(), velocidadDisparos));
            disparos.push_back(
                    new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f + 10,
                                this->getPosicionY(), velocidadDisparos));
            this->cantidadDisparos+= 2;
        } else if (this->estadoPowerUP == ESTADO_POWER_UP_AVIONES_SECUNDARIOS){
            // disparos.push_back(
            //         new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f - 25,
            //                     this->getPosicionY() + 15, velocidadDisparos));
            disparos.push_back(new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f,
                                           this->getPosicionY(), velocidadDisparos));
            // disparos.push_back(
            //         new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f + 25,
            //                     this->getPosicionY() + 15, velocidadDisparos));
            this->cantidadDisparos+= 1;
        } else if (this->estadoPowerUP == ESTADO_POWER_UP_DOBLE){
            disparos.push_back(
                    new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f - 25,
                                this->getPosicionY() + 15, velocidadDisparos));
            disparos.push_back(
                    new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f - 10,
                                this->getPosicionY(), velocidadDisparos));
            disparos.push_back(
                    new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f + 10,
                                this->getPosicionY(), velocidadDisparos));
            disparos.push_back(
                    new Disparo(this->getPosicionX() + ANCHO_AVION_COMUN / 2.f - ANCHO_DISPARO_COMUN / 2.f + 25,
                                this->getPosicionY() + 15, velocidadDisparos));
            this->cantidadDisparos+= 4;
        }
    }
    // for(int i = 0; i < disparos.size(); i++){
    //     cout << "DISPARO AVION COMUN: " << disparos[i]->getPosX() << endl;
    //     cout << "DISPARO AVION COMUN: " << disparos[i]->getPosY() << endl;
    // }
    return disparos;
}

void Avion::volverEstadoInicial(bool inmunidad){
    this->velocidadX = 0;
    this->velocidadY = 0;
    this->posX = this->posXInicial;
    this->posY = this->posYInicial;
    if (this->vidas != 0) {
        this->estadoPowerUP = ESTADO_SIN_POWER_UP;
        if (inmunidad) {
            this->contadorTiempoInmunidad = TIEMPO_INMUNIDAD;
            this->contadorIntermitenciaInmunidad = TIEMPO_INTERMITENCIA;
        }
        this->colisionable->mover(this->posX, this->posY, 0, TIPO_AVION);
        if (this->estadoAnimacion != DESCONECTADO)
            this->estadoAnimacion = ESTADO_NORMAL;
    } else {
        this->estadoAnimacion = ESTADO_AVION_DESTRUIDO;
    }
}

string Avion::getIdSprite(){
    return this->idSprite;
}

string Avion::getIdSpriteDisparos() {
    return this->idSpriteDisparos;
}

void Avion::setPosicion(float x, float y) {
    posX = x;
    posY = y;
}

void Avion::sumarPuntos(int puntos) {
    pthread_mutex_lock(&this->mutexPuntaje);
    this->puntaje += puntos;
    pthread_mutex_unlock(&this->mutexPuntaje);
}

Colisionable* Avion::getColisionable(){
    return this->colisionable;
}

void Avion::colisionar(){
    if (this->contadorTiempoInmunidad == 0) {
        // cout << "ESTADO ANIMACION: " << this->estadoAnimacion << endl;
        // if((this->estadoAnimacion < AVION_TRANSFORMADO_EXPLOSION_ETAPA_1) && (this->estadoAnimacion > EXPLOSION_ETAPA_10)){
        //     if((contadorColisiones > 0) && ((this->estadoPowerUP == ESTADO_POWER_UP_AVIONES_SECUNDARIOS) || (this->estadoPowerUP == ESTADO_POWER_UP_DOBLE))){
        //         contadorColisiones--;
        //         this->estadoAnimacion = AVION_TRANSFORMADO_EXPLOSION_ETAPA_1;
        //         cout << "CONTADOR COLISIONES: " << contadorColisiones << endl;
        //     }
        // }
        if (this->estadoAnimacion < EXPLOSION_ETAPA_1) {
            this->estadoAnimacion = EXPLOSION_ETAPA_1 ;
            if (this->vidas > 0) {
                pthread_mutex_lock(&this->mutexVidas);
                quitarUnaVida();
                pthread_mutex_unlock(&this->mutexVidas);
            } else {
            }
        }
    }
}

void Avion::colisionarConPowerUp(){
    if (this->estadoAnimacion < EXPLOSION_ETAPA_1 )
        this->estadoAnimacion = COLISION_AVION_CON_POWERUP;
}

void Avion::resetPuntos() {
    pthread_mutex_lock(&this->mutexPuntaje);
    this->puntaje = 0;
    pthread_mutex_unlock(&this->mutexPuntaje);
}

int Avion::getPuntaje() {
    pthread_mutex_lock(&this->mutexPuntaje);
    int puntaje = this->puntaje;
    pthread_mutex_unlock(&this->mutexPuntaje);
    return puntaje;
}

int Avion::getVidas() {
    return this->vidas;
}

void Avion::quitarUnaVida() {
    this->vidas--;
}

void Avion::setSpawn(int x, int y) {
    posXInicial = x;
    posYInicial = y;
}

float Avion::getContadorTiempoInmunidad() {
    return this->contadorTiempoInmunidad;
}

bool Avion::moverAPosicionFinal(float timeStep) {
    bool resultado = false;
    pthread_mutex_lock(&this->mutexMover);
    if (this->estadoAnimacion != ESTADO_AVION_DESTRUIDO) {
        this->estadoAnimacion = ESTADO_NORMAL;
        if (this->posX != this->posXFinal || this->posY != this->posYFinal) {
            if (this->posX != this->posXFinal) {
                if (this->posX < this->posXFinal) {
                    if ((this->posX + this->velocidad / 2 * timeStep) < this->posXFinal)
                        this->posX += this->velocidad / 2 * timeStep;
                    else
                        this->posX = this->posXFinal;
                } else {
                    if ((this->posX - this->velocidad / 2 * timeStep) > this->posXFinal)
                        this->posX -= this->velocidad * timeStep;
                    else
                        this->posX = this->posXFinal;
                }
            } else {
                if (this->posY < this->posYFinal) {
                    if ((this->posY + this->velocidad / 2 * timeStep) < this->posYFinal)
                        this->posY += this->velocidad / 2 * timeStep;
                    else
                        this->posY = this->posYFinal;
                } else {
                    if ((this->posY - this->velocidad / 2 * timeStep) > this->posYFinal)
                        this->posY -= this->velocidad / 2 * timeStep;
                    else
                        this->posY = this->posYFinal;
                }
            }
        } else {
            this->estadoAnimacion = ESTACIONADO;
            resultado = true;
        }
    } else {
        resultado = true;
    }
    pthread_mutex_unlock(&this->mutexMover);
    return resultado;
}

void Avion::setPowerUpAmetralladoras() {
    if(this->estadoPowerUP == ESTADO_POWER_UP_AVIONES_SECUNDARIOS){
        this->estadoPowerUP = ESTADO_POWER_UP_DOBLE;
    }else{
        this->estadoPowerUP = ESTADO_POWER_UP_DISPARO_DOBLE;
    }
}

void Avion::setPowerUpAvionesSecundarios() {
    if(this->estadoPowerUP == ESTADO_POWER_UP_DISPARO_DOBLE){
        this->estadoPowerUP = ESTADO_POWER_UP_DOBLE;
    }else{
        this->estadoPowerUP = ESTADO_POWER_UP_AVIONES_SECUNDARIOS;
    }
}

int Avion::getEstadoPowerUp(){
    return this->estadoPowerUP;
}

int Avion::getNumeroAvion(){
    return this->numeroAvion;
}

bool Avion::estaColisionando(){
    return (this->estadoAnimacion >= EXPLOSION_ETAPA_1);
}

void Avion::aumentarAciertos() {
    this->cantidadAciertos ++;
}

int Avion::getCantidadAciertos() {
    return this->cantidadAciertos;
}

int Avion:: getCantidadDisparos() {
    return this->cantidadDisparos;
}

int Avion::getPorcentajeAciertos() {
    if (this->cantidadDisparos != 0){
        return (int) floor(100 * (this->cantidadAciertos / (float) this->cantidadDisparos));
    } else {
        return 0;
    }
}

void Avion::cargarListaAvionesSecundarios(){
    while(!this->avionesSecundarios.empty()) delete this->avionesSecundarios.front(), this->avionesSecundarios.pop_front();

    AvionSecundario* avionIzquierdo = new AvionSecundario(this->posX - (ANCHO_AVION_COMUN/2), this->posY, this->velocidad, this->velocidadDisparos, this->idSpriteDisparos, this->posXFinal - ANCHO_AVION_SECUNDARIO, this->posYFinal);
    AvionSecundario* avionDerecho = new AvionSecundario(this->posX + (ANCHO_AVION_SECUNDARIO +ANCHO_AVION_COMUN/2) , this->posY, this->velocidad, this->velocidadDisparos, this->idSpriteDisparos, this->posXFinal + ANCHO_AVION_SECUNDARIO, this->posYFinal);
    if(this->velocidadX < 0){
        avionDerecho->manejarEvento(IZQUIERDA_PRESIONA);
        avionIzquierdo->manejarEvento(IZQUIERDA_PRESIONA);
    } else if (this->velocidadX > 0) {
        avionDerecho->manejarEvento(DERECHA_PRESIONA);
        avionIzquierdo->manejarEvento(DERECHA_PRESIONA);
    }

    if(this->velocidadY < 0) {
        avionDerecho->manejarEvento(ARRIBA_PRESIONA);
        avionIzquierdo->manejarEvento(ARRIBA_PRESIONA);
    } else if(this->velocidadY > 0) {
        avionDerecho->manejarEvento(ABAJO_PRESIONA);
        avionIzquierdo->manejarEvento(ABAJO_PRESIONA);
    }
    this->avionesSecundarios.push_back(avionIzquierdo);
    this->avionesSecundarios.push_back(avionDerecho);
}

void Avion::setAvionesSecundarios(list<AvionSecundario*> avionesSecundarios){
  this->avionesSecundarios = avionesSecundarios;
}

list<AvionSecundario*>& Avion::getAvionesSecundarios(){
  return this->avionesSecundarios;
}
