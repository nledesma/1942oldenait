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

void Celda::limpiarCelda(){
    aviones.clear();
    disparosAmigos.clear();
}

void Celda::verificarColisiones(){
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
}
