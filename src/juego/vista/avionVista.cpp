#include "avionVista.hpp"

void AvionVista::actualizar(string codigo){
    memcpy((void*) &(this->posX), (void*) &(codigo[0]), sizeof(float));
    memcpy((void*) &(this->posY), (void*) &(codigo[sizeof(float)]), sizeof(float));
    estadoAnimacion = (int) codigo[2*sizeof(float)];
}
