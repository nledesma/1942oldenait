#include <iostream>
#include "ventana.hpp"
#include "avion.hpp"
#include "escenario.hpp"
#include "figura.hpp"
#include "servidor.hpp"
#include "servidorParser.hpp"
using namespace std;

int main(){
  Servidor* servidor;
  ServidorParser parser;
  servidor = parser.deserializar("servidor.xml");
  int ancho = servidor->getEscenario()->getVentana()->getAncho();
  int alto = servidor->getEscenario()->getVentana()->getAlto();

  Escenario* unEscenario = new Escenario(ancho,alto);
  unEscenario->iniciar("galaxia2.bmp");
  //SDL_Delay(6000);
  bool quit = false;
  //Event handler
  SDL_Event e;
  //While application is running
  while( !quit ){
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ){
      //User requests quit
      if( e.type == SDL_QUIT ){
        quit = true;
      }
    }
  }
  delete unEscenario;
  return 0;
}
