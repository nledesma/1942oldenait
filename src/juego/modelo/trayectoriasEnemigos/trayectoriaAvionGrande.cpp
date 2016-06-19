#include "trayectoriaAvionGrande.hpp"
#include "movimientoAvionGrandeEtapa1.hpp"
#include "movimientoAvionGrandeEtapa2.hpp"

TrayectoriaAvionGrande::TrayectoriaAvionGrande() {
    MovimientoAvionGrandeEtapa1 * movimientoEtapa1 = new MovimientoAvionGrandeEtapa1(40);
    MovimientoAvionGrandeEtapa2 * movimientoEtapa2 = new MovimientoAvionGrandeEtapa2();
    this->movimientos.push_back(movimientoEtapa1);
    this->movimientos.push_back(movimientoEtapa2);
    this->itMovimientos = movimientos.begin();
}

TrayectoriaAvionGrande::~TrayectoriaAvionGrande() { }

void TrayectoriaAvionGrande::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion,
                                float timestep) {
    /* Si la cola no está vacía se comporta según el próximo tipo de movimiento */
    if (this->itMovimientos != movimientos.end()) {
        TipoMovimiento* proximoTipoMovimiento = (*this->itMovimientos);
        bool termino;
        termino = proximoTipoMovimiento->mover(posX, posY, velocidad, angulo, estadoAnimacion, timestep);

        if (termino)
            ++this->itMovimientos;
        /* De lo contrario la trayectoria continua en línea recta indefinidamente hasta salir de la pantalla */
    } else {
        float velocidadX = velocidad * Trigonomaster::getCoseno(angulo, estadoAnimacion);
        float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo, estadoAnimacion));

        posX += velocidadX*timestep;
        posY += velocidadY*timestep;
    }
}

void TrayectoriaAvionGrande::setEstadoInicial() {
    for (list<TipoMovimiento *>::iterator iterador = movimientos.begin(); iterador != movimientos.end(); iterador++) {
        TipoMovimiento* movimiento = (*iterador);
        movimiento->setEstadoInicial();
    }
    this->itMovimientos = this->movimientos.begin();
}