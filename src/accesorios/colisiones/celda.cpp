#include "celda.hpp"

Celda::Celda(){

}

void Celda::agregarAvion(Avion * avion){
    aviones.push_back(avion);
}
//
void Celda::agregarEnemigo(AvionEnemigo * enemigo){
    enemigos.push_back(enemigo);
}

void Celda::agregarDisparoAmigo(Disparo * disparo){
    disparosAmigos.push_back(disparo);
}

void Celda::agregarPowerUp(PowerUp* powerUp){
  powerUps.push_back(powerUp);
}

void Celda::limpiarCelda(){
    aviones.clear();
    disparosAmigos.clear();
    enemigos.clear();
    powerUps.clear();
}

void Celda::verificarColisiones(){

    // if(aviones.size() > 0 && enemigos.size() > 0) {
    //     cout << "Tamanio listas: " << aviones.size() << " " << enemigos.size() << endl;
    // }

    for(list<Avion*>::iterator itAviones = this->aviones.begin(); itAviones != this->aviones.end(); itAviones++){
        for(list<AvionEnemigo*>::iterator itEnemigos = this->enemigos.begin(); itEnemigos != this->enemigos.end(); itEnemigos++){
            if((*itAviones)->getColisionable()->colisiona((*itEnemigos)->getColisionable())){
                (*itAviones)->colisionar();
                (*itEnemigos)->colisionar();
            }
        }
    }

    for(list<AvionEnemigo*>::iterator itEnemigos = this->enemigos.begin(); itEnemigos != this->enemigos.end(); itEnemigos++){
        for(list<Disparo*>::iterator itDisparos = this->disparosAmigos.begin(); itDisparos != this->disparosAmigos.end(); itDisparos++){
            if((*itEnemigos)->getColisionable()->colisiona((*itDisparos)->getColisionable())){
                (*itEnemigos)->colisionar();
                (*itDisparos)->colisionar();
            }
        }
    }

    for(list<Avion*>::iterator itAviones = this->aviones.begin(); itAviones != this->aviones.end(); itAviones++){
        for(list<PowerUp*>::iterator itPowerUps = this->powerUps.begin(); itPowerUps != this->powerUps.end(); itPowerUps++){
            if((*itAviones)->getColisionable()->colisiona((*itPowerUps)->getColisionable())){
                (*itAviones)->colisionarConPowerUp();
                (*itPowerUps)->colisionar();
            }
        }
    }
}
