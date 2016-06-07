#include "trayectoriaRulo.hpp"

TrayectoriaRulo::~TrayectoriaRulo() { }

TrayectoriaRulo::TrayectoriaRulo() {
    Desplazamiento * desplazamientoRecto1 = new Desplazamiento(1, 0);
    Giro * giro1 = new Giro(360, (float)-100);
    this->colaMovimientos.push(desplazamientoRecto1);
    this->colaMovimientos.push(giro1);

}

void TrayectoriaRulo::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion,
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