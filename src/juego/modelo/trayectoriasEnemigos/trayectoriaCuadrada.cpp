#include "trayectoriaCuadrada.hpp"

TrayectoriaCuadrada::~TrayectoriaCuadrada() { }

TrayectoriaCuadrada::TrayectoriaCuadrada() {
    Desplazamiento * desplazamientoRecto1 = new Desplazamiento(20, 0);
    Giro * giro1 = new Giro(90, (float)-5.625);
    Desplazamiento * desplazamientoRecto2 = new Desplazamiento(10, 0);
    Giro * giro2 = new Giro(90, (float)-5.625);
    this->colaMovimientos.push(desplazamientoRecto1);
    this->colaMovimientos.push(giro1);
    this->colaMovimientos.push(desplazamientoRecto2);
    this->colaMovimientos.push(giro2);

}