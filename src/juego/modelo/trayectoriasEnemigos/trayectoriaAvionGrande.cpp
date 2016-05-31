#include "trayectoriaAvionGrande.hpp"
#include "movimientoAvionGrandeEtapa1.hpp"
#include "movimientoAvionGrandeEtapa2.hpp"

TrayectoriaAvionGrande::TrayectoriaAvionGrande() {
    MovimientoAvionGrandeEtapa1 * movimientoEtapa1 = new MovimientoAvionGrandeEtapa1(40);
    MovimientoAvionGrandeEtapa2 * movimientoEtapa2 = new MovimientoAvionGrandeEtapa2();
    this->colaMovimientos.push(movimientoEtapa1);
    this->colaMovimientos.push(movimientoEtapa2);
}

TrayectoriaAvionGrande::~TrayectoriaAvionGrande() { }

void TrayectoriaAvionGrande::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion,
                                float timestep) {
    /* Si la cola no está vacía se comporta según el próximo tipo de movimiento */
    if (!this->colaMovimientos.empty()) {
        TipoMovimiento* proximoTipoMovimiento = this->colaMovimientos.front();
        bool termino;
        termino = proximoTipoMovimiento->mover(posX, posY, velocidad, angulo, estadoAnimacion, timestep);

        if (termino)
            this->colaMovimientos.pop();
        /* De lo contrario la trayectoria continua en línea recta indefinidamente hasta salir de la pantalla */
    } else {
        float velocidadX = velocidad * Trigonomaster::getCoseno(angulo, estadoAnimacion);
        float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo, estadoAnimacion));

        posX += velocidadX*timestep;
        posY += velocidadY*timestep;
    }
}