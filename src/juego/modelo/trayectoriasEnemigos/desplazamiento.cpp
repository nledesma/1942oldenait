#include "desplazamiento.hpp"

Desplazamiento::Desplazamiento(float cantidadTimesteps, float velocidadAngular){
  this-> cantidadTimesteps = cantidadTimesteps;
  this-> velocidadAngular = velocidadAngular;
  this-> cantidadTimestepsInicial = cantidadTimesteps;
  this-> velocidadAngularInicial = velocidadAngular;
}

bool Desplazamiento::mover(float &posX, float &posY, float &velocidad, float &angulo, int &estadoAnimacion, float timestep) {
  float velocidadX = velocidad * Trigonomaster::getCoseno(angulo, estadoAnimacion);
  float velocidadY = -(velocidad * Trigonomaster::getSeno(angulo, estadoAnimacion));
  posX += velocidadX * timestep;
  posY += velocidadY * timestep;

  cantidadTimesteps = cantidadTimesteps - timestep;

  return (cantidadTimesteps <= 0);
}

void Desplazamiento::setEstadoInicial() {
  this->velocidadAngular = this->velocidadAngularInicial;
  this->cantidadTimesteps = this->cantidadTimestepsInicial;
}
