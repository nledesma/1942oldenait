#include <iostream>
#include "ventana.hpp"
#include "avion.hpp"
#include "escenario.hpp"
#include "figura.hpp"
#include "servidor.hpp"
#include "servidorParser.hpp"
#include <stdio.h>
using namespace std;

int main(){
  Servidor* servidor;
  ServidorParser parser;
  servidor = parser.deserializar("servidorCompleto.xml");
  const char* path = servidor->getEscenario()-> getFondoSprite();
  servidor->getEscenario()->iniciar(string(path) + ".bmp");

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
  delete servidor->getEscenario();
  return 0;
}
