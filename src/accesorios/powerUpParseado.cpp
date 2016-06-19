#include "powerUpParseado.hpp"

using namespace std;

PowerUpParseado::PowerUpParseado() {
    tipo = "";
    posX = 0;
    posY = 0;
    valor = 0;
}

PowerUpParseado::~PowerUpParseado() { }

void PowerUpParseado::setTipo(string tipo){
  this->tipo = tipo;
}

void PowerUpParseado::setValor(int valor){
  this->valor = valor;
}

void PowerUpParseado::setPosX(float posX){
  this->posX = posX;
}

void PowerUpParseado::setPosY(float posY){
  this->posY = posY;
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

float PowerUpParseado::getPosX(){
  return this->posX;
}

float PowerUpParseado::getPosY(){
  return this->posY;
}

int PowerUpParseado::getValor(){
  return this->valor;
}
