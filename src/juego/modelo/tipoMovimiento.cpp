#include "tipoMovimiento.hpp"

void TipoMovimiento::TipoMovimiento(float cantidadTimesteps, float velocidadAngular){
  this-> cantidadTimesteps = cantidadTimesteps;
  this-> velocidadAngular = velocidadAngular;
}

bool TipoMovimiento::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep) {
  
}
