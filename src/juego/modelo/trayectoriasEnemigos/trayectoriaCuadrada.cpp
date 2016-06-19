#include "trayectoriaCuadrada.hpp"

TrayectoriaCuadrada::~TrayectoriaCuadrada() { }

TrayectoriaCuadrada::TrayectoriaCuadrada() {
    Desplazamiento * desplazamientoRecto1 = new Desplazamiento(1, 0);
    Giro * giro1 = new Giro(90, (float)-50);
    Desplazamiento * desplazamientoRecto2 = new Desplazamiento(1, 0);
    Giro * giro2 = new Giro(90, (float)-50);
    this->movimientos.push_back(desplazamientoRecto1);
    this->movimientos.push_back(giro1);
    this->movimientos.push_back(desplazamientoRecto2);
    this->movimientos.push_back(giro2);
    this->itMovimientos = this->movimientos.begin();

}

void TrayectoriaCuadrada::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion,
                        float timestep) {
    /* Si la cola no está vacía se comporta según el próximo tipo de movimiento */
    if (this->itMovimientos != this->movimientos.end()) {
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

void TrayectoriaCuadrada::setEstadoInicial() {
    for (list<TipoMovimiento *>::iterator iterador = movimientos.begin(); iterador != movimientos.end(); iterador++) {
        TipoMovimiento* movimiento = (*iterador);
        movimiento->setEstadoInicial();
    }
    this->itMovimientos = this->movimientos.begin();
}