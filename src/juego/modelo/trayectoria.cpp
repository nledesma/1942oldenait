#include "trayectoria.hpp"

void Trayectoria::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion,
                        float timestep) {
    /* Si la cola no está vacía se comporta según el próximo tipo de movimiento */
    if (!this->colaMovimientos.empty()) {
        TipoMovimiento proximoTipoMovimiento = this->colaMovimientos.front();
        bool termino;
        termino = proximoTipoMovimiento.mover(posX, posY, velocidad, angulo, estadoAnimacion, timestep);

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