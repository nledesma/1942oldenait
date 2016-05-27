#include "desplazamiento.hpp"

void Desplazamiento::Desplazamiento(float cantidadTimesteps, float velocidadAngular){
  this-> cantidadTimesteps = cantidadTimesteps;
  this-> velocidadAngular = velocidadAngular;
}

bool Desplazamiento::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep) {
  float velocidadX = velocidad * Trigonomaster::getCoseno(angulo, estadoAnimacion);
  float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo, estadoAnimacion));

  posX += velocidadX*timestep;
  posY += velocidadY*timestep;

  cantidadTimesteps--;

  if(cantidadTimesteps > 0){
    return false;
  } else {
    return true;
  }
}
