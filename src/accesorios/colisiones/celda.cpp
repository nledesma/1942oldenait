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
                cout << "Colisiono" << endl;
            }
            /*else {
            *//*    cout << "Posicion enemigo" << endl;
                int* posCelda = (*itEnemigos)->getColisionable()->getPosCeldas();
*//**//*                cout << (*itEnemigos)->getTipoAvion() << endl;
                cout << posCelda[0] << " " << posCelda[1] << " " << posCelda[2] << " " << posCelda[3] << endl;
                cout << (*itEnemigos)->getColisionable()->getSuperficiePrincipal()->getIzqAbajo()->getPosX() << " " << (*itEnemigos)->getColisionable()->getSuperficiePrincipal()->getIzqAbajo()->getPosY() << endl;
                cout << (*itEnemigos)->getColisionable()->getSuperficiePrincipal()->getIzqArriba()->getPosX() << " " << (*itEnemigos)->getColisionable()->getSuperficiePrincipal()->getIzqArriba()->getPosY() << endl;
                cout << (*itEnemigos)->getColisionable()->getSuperficiePrincipal()->getDerArriba()->getPosX() << " " << (*itEnemigos)->getColisionable()->getSuperficiePrincipal()->getDerArriba()->getPosY() << endl;
                cout << (*itEnemigos)->getColisionable()->getSuperficiePrincipal()->getDerAbajo()->getPosX() << " " << (*itEnemigos)->getColisionable()->getSuperficiePrincipal()->getDerAbajo()->getPosY() << endl;
                cout << endl << endl;
                cout << "Posicion disparo" << endl;
                cout << (*itDisparos)->getColisionable()->getSuperficiePrincipal()->getIzqAbajo()->getPosX() << " " << (*itDisparos)->getColisionable()->getSuperficiePrincipal()->getIzqAbajo()->getPosY() << endl;
                cout << (*itDisparos)->getColisionable()->getSuperficiePrincipal()->getIzqArriba()->getPosX() << " " << (*itDisparos)->getColisionable()->getSuperficiePrincipal()->getIzqArriba()->getPosY() << endl;
                cout << (*itDisparos)->getColisionable()->getSuperficiePrincipal()->getDerArriba()->getPosX() << " " << (*itDisparos)->getColisionable()->getSuperficiePrincipal()->getDerArriba()->getPosY() << endl;
                cout << (*itDisparos)->getColisionable()->getSuperficiePrincipal()->getDerAbajo()->getPosX() << " " << (*itDisparos)->getColisionable()->getSuperficiePrincipal()->getDerAbajo()->getPosY() << endl;
                cout << endl << endl;*//**//*
            }*/
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
