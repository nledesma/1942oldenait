#include "temporizador.hpp"

using namespace std;

Temporizador::Temporizador(){
  ticksIniciales = 0;
  pausarTicks = 0;

  pausado = false;
  iniciado = false;
}

void Temporizador::comenzar(){
  iniciado = true;
  pausado = false;

  ticksIniciales = SDL_GetTicks();
  pausarTicks = 0;
}

void Temporizador::detener() {

  iniciado = false;
  pausado = false;

  ticksIniciales = 0;
  pausarTicks = 0;
}

void Temporizador::pausar(){
  if( iniciado && !pausado ) {
    pausado = true;
    pausarTicks = SDL_GetTicks() - ticksIniciales;
    ticksIniciales = 0;
  }
}

void Temporizador::reanudar() {
  if( iniciado && pausado){
    pausado = false;

    ticksIniciales = SDL_GetTicks() - pausarTicks;

    pausarTicks = 0;
  }
}

Uint32 Temporizador::getTicks() {
  Uint32 tiempo = 0;
  if(iniciado) {
    if(pausado){
      tiempo = pausarTicks;
    } else {
      tiempo = SDL_GetTicks() - ticksIniciales;
    }
  }
  return tiempo;
}

bool Temporizador::estaIniciado(){
  return iniciado;
}

bool Temporizador::estaPausado(){
  return pausado && iniciado;
}
