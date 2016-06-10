#include "grilla.hpp"

Grilla::Grilla(int cantFilas, int cantColumnas){
    this->anchoCeldas = ANCHO_ESCENARIO / cantColumnas;
    this->altoCeldas = ALTO_ESCENARIO / cantFilas;
    this->cantFilas = cantFilas;
    this->cantColumnas = cantColumnas;
    for(int i = 0; i < cantFilas; i++){
        list<Celda*> fila;
        for(int j = 0; j < cantColumnas; j++){
            fila.push_back(new Celda());
        }
        this->grilla.push_back(fila);
    }
}

Grilla::~Grilla(){
    for(list<list<Celda*>>::iterator itFilas = grilla.begin(); itFilas != grilla.end(); itFilas++){
        for(list<Celda*>::iterator itColumnas = (*itFilas).begin(); itColumnas != (*itFilas).end(); itColumnas++){
            delete (*itColumnas);
        }
    }
}

void Grilla::ubicarAviones(list<Avion*> aviones){
    for(list<Avion*>::iterator itAviones = aviones.begin(); itAviones != aviones.end(); itAviones++){
        list<Celda*> celdas = this->ubicarEnCeldas((*itAviones)->getColisionable());
        for(list<Celda*>::iterator itCeldas = celdas.begin(); itCeldas != celdas.end(); itCeldas++){
            (*itCeldas)->agregarAvion((*itAviones));
        }
    }
}

void Grilla::ubicarDisparosAmigos(list<Disparo*> disparos){
    for(list<Disparo*>::iterator itDisparos = disparos.begin(); itDisparos != disparos.end(); itDisparos++){
        list<Celda*> celdas = this->ubicarEnCeldas((*itDisparos)->getColisionable());
        for(list<Celda*>::iterator itCeldas = celdas.begin(); itCeldas != celdas.end(); itCeldas++){
            (*itCeldas)->agregarDisparoAmigo((*itDisparos));
        }
    }
}

void Grilla::ubicarEnemigos(list<AvionEnemigo*> enemigos){
    for(list<AvionEnemigo*>::iterator itEnemigos = enemigos.begin(); itEnemigos != enemigos.end(); itEnemigos++){
        list<Celda*> celdas = this->ubicarEnCeldas((*itEnemigos)->getColisionable());
        for(list<Celda*>::iterator itCeldas = celdas.begin(); itCeldas != celdas.end(); itCeldas++){
            (*itCeldas)->agregarEnemigo((*itEnemigos));
        }
    }
}

void Grilla::ubicarPowerUps(list<PowerUp*> powerUps){
    for(list<PowerUp*>::iterator itPowerUps = powerUps.begin(); itPowerUps != powerUps.end(); itPowerUps++){
        list<Celda*> celdas = this->ubicarEnCeldas((*itPowerUps)->getColisionable());
        for(list<Celda*>::iterator itCeldas = celdas.begin(); itCeldas != celdas.end(); itCeldas++){
            (*itCeldas)->agregarPowerUp((*itPowerUps));
        }
    }
}

void Grilla::verificarColisiones(){
    for(list<list<Celda*>>::iterator itFilas = this->grilla.begin(); itFilas != this->grilla.end(); itFilas++){
        for(list<Celda*>::iterator itColumna = (*itFilas).begin(); itColumna != (*itFilas).end(); itColumna++){
            (*itColumna)->verificarColisiones();
        }
    }
}

void Grilla::limpiarGrilla(){
    for(list<list<Celda*>>::iterator itFilas = this->grilla.begin(); itFilas != this->grilla.end(); itFilas++){
        for(list<Celda*>::iterator itColumna = (*itFilas).begin(); itColumna != (*itFilas).end(); itColumna++){
            (*itColumna)->limpiarCelda();
        }
    }
}


list<Celda*> Grilla::ubicarEnCeldas(Colisionable * colisionable){

    int colDerecha = colisionable->getExtremoDerecho() / this->anchoCeldas;
    int colIzquierda = colisionable->getExtremoIzquierdo() / this->anchoCeldas;
    int filaAbajo = colisionable->getExtremoInferior() / this->altoCeldas;
    int filaArriba = colisionable->getExtremoSuperior() / this->altoCeldas;

    list<Celda*> celdas;
    if (filaAbajo >= 0 && filaAbajo < this->cantFilas && filaArriba >= 0 && filaArriba < this->cantFilas &&
            colIzquierda >= 0 && colIzquierda < this->cantColumnas && colDerecha >= 0 && colDerecha < this->cantColumnas){
        list<list<Celda*>>::iterator itFilas = this->grilla.begin();
        advance(itFilas, filaAbajo);
        list<Celda*>::iterator itColumna = (*itFilas).begin();
        advance(itColumna, colIzquierda);
        celdas.push_back((*itColumna));
        if((filaAbajo == filaArriba) && (colIzquierda == colDerecha)){
            return celdas;
        }


        if((filaAbajo == filaArriba) && (colIzquierda != colDerecha)){
            int columnas = colIzquierda - colDerecha;
            for(int i = 0; i < columnas; i++){
                advance(itColumna, 1);
                celdas.push_back((*itColumna));
            }
            return celdas;
        }
        int cantFilas = filaArriba - filaAbajo - 1;
        for(int i = 0; i < cantFilas; i++){
            advance(itFilas, 1);
            itColumna = (*itFilas).begin();
            advance(itColumna, colIzquierda);
            celdas.push_back((*itColumna));
            int columnas = colIzquierda - colDerecha;
            for(int i = 0; i < columnas; i++){
                advance(itColumna, 1);
                celdas.push_back((*itColumna));
            }
        }
    }
    return celdas;
}
