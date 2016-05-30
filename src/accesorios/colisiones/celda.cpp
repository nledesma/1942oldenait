#include "celda.hpp"

Celda::Celda(){

}

void Celda::agregarAvion(Avion * avion){
    aviones.push_back(avion);
}
//
void Celda::agregarEnemigos(AvionEnemigo * enemigo){
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
        for(list<Disparo*>::iterator itEnemigos = this->disparosAmigos.begin(); itEnemigos != this->disparosAmigos.end(); itEnemigos++){
            if((*itAviones)->getColisionable()->colisiona((*itEnemigos)->getColisionable())){
                (*itAviones)->colisionar();
            }
        }
    }
}
