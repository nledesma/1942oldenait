#include <iostream>
#include "ventana.hpp"
#include "avion.hpp"
#include "escenario.hpp"
#include "figura.hpp"
using namespace std;

int main(){
  //Avion* unAvion = new Avion();
  //cout << "ESTO ES EL RENDERER DE LA VENTANA " << ventana->getRenderer() << endl;
  Escenario* unEscenario = new Escenario(800,600);
  unEscenario->iniciar("galaxia2.bmp");
  //SDL_Delay(6000);
  bool quit = false;

  //Event handler
  SDL_Event e;

  //While application is running
  while( !quit )
  {
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
      //User requests quit
      if( e.type == SDL_QUIT )
      {
        quit = true;
      }
    }
  delete unEscenario;
  //delete unAvion;
}
  return 0;
}
