#include "powerUpParseado.hpp"

using namespace std;

PowerUpParseado::PowerUpParseado() {}

PowerUpParseado::~PowerUpParseado() { }

void PowerUpParseado::setTipo(string tipo){
  this->tipo = tipo;
}

void PowerUpParseado::setCantidad(int cantidad){
  this->cantidad = cantidad;
}

void PowerUpParseado::setValor(int valor){
  this->valor = valor;
}

int PowerUpParseado::getTipo(){
  if (this->tipo == "bonificacion"){
    return TIPO_POWERUP_BONIFICACION;
  } else if(this->tipo == "aviones"){
    return TIPO_POWERUP_AVIONES_SECUNDARIOS;
  } else if(this->tipo == "ametralladoras"){
    return TIPO_POWERUP_DOS_AMETRALLADORAS;
  } else if(this->tipo == "destruir"){
    return TIPO_POWERUP_DESTRUIR_ENEMIGOS;
  } else return 0;
}

int PowerUpParseado::getCantidad(){
  return this->cantidad;
}

int PowerUpParseado::getValor(){
  return this->valor;
}
