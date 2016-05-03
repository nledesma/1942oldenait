#include <iostream>
#include "ventana.hpp"
#include "avion.hpp"
#include "escenario.hpp"
#include "figura.hpp"
#include "servidor.hpp"
#include "servidorParser.hpp"
#include <stdio.h>
using namespace std;

void* apagarServidor(void* servidor){

    char caracter;

    Servidor *servidor1 = (Servidor *) servidor;
    do{
      cout << "Presione 'S' para salir" << endl;
      cin >> caracter;
    }while((caracter != 's')&&(caracter != 'S'));

    if((caracter == 's')||(caracter == 'S')){
        servidor1->cerrar();
    }
    pthread_exit(NULL);
}


int main(){
  Servidor* servidor;
  ServidorParser parser;
  servidor = parser.deserializar("servidorCompleto.xml");

  pthread_t apagar;
  pthread_create(&apagar,NULL,apagarServidor,servidor);
  // Servidor aceptando conexiones
  try{
    servidor->pasivar();
  }catch(runtime_error &e){
      Logger::instance()->logError(errno,"Se produjo un error en el listen");
  }

  pthread_join(apagar, NULL);
  Logger::instance()->cerrar();
  Logger::resetInstance();
 
  pthread_exit(NULL);

  //Esto detiene el funcionamiento del thread de salida
  bool quit = false;
  SDL_Event e; //Event handler

  while(!quit){ //While application is running
    while( SDL_PollEvent( &e ) != 0 ){ //Handle events on queue
      if( e.type == SDL_QUIT ){ //User requests quit
        quit = true;
      }
    }
  }
  
  delete servidor->getEscenario();

  return 0;
}
