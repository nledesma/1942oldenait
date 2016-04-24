#include <iostream>
#include "ventana.hpp"
#include "avion.hpp"
using namespace std;

int main(){

  //Por ahora para probar le paso estos valores, pero en realidad son los que deberian ser pasados por el XML
  Ventana* ventana = new Ventana(640, 480);
  Avion* unAvion = new Avion();
  ventana->iniciar();
  //Clear screen
  SDL_SetRenderDrawColor(ventana->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(ventana->getVentanaRenderer());
  //Render background texture to screen
	ventana->getVentanaTextura().render(0, 0);
	//Render Mario :) to the screen
	unAvion->getAvionTextura().render(240, 190);
	//Update screen
	SDL_RenderPresent(ventana->getVentanaRenderer());
  //Elimino la ventana
  delete ventana;
  delete unAvion;

  return 0;
}
