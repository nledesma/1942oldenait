#include <iostream>
#include "ventana.hpp"
#include "avion.hpp"
#include "escenario.hpp"
using namespace std;

int main(){
  //Avion* unAvion = new Avion();
  //cout << "ESTO ES EL RENDERER DE LA VENTANA " << ventana->getRenderer() << endl;
  Escenario* unEscenario = new Escenario(800,600);
  unEscenario->iniciar("foo.png");
  SDL_Delay(2000);
  //Clear screen
  //SDL_SetRenderDrawColor(ventana->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderClear(ventana->getVentanaRenderer());
  //Render background texture to screen
	//ventana->getVentanaTextura().render(0, 0);
	//Render Mario :) to the screen
	//unAvion->getAvionTextura().render(240, 190);
	//Update screen
	//SDL_RenderPresent(ventana->getVentanaRenderer());
  //Elimino la ventana
  delete unEscenario;
  //delete unAvion;

  return 0;
}
