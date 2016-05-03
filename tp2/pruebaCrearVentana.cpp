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

bool archivoExiste (const string& archivo) {
    if (FILE *file = fopen(archivo.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

int main(int argc, char *argv[]){
    string rutaXMLServidor;

    if (argc < 2){
        cout << "Argumentos insuficientes, se utilizará el XML por defecto" << endl;
        Logger::instance()->logWarning("No se ingresó la cantidad de parámetros suficientes. Se inicializa el servidor con el XML por defecto.");
        rutaXMLServidor = "servidorCompleto.xml";
    } else {
        if (archivoExiste(argv[1])){
          rutaXMLServidor = argv[1];  
        } else {
          rutaXMLServidor = "servidorCompleto.xml";
          cout << "El parámetro ingresado no es válido. Se inicializa el servidor con el XML por defecto" << endl;
          Logger::instance()->logWarning("El parámetro ingresado no es válido. Se inicializa el servidor con el XML por defecto.");
        }
    }

  Servidor* servidor;
  ServidorParser parser;
  servidor = parser.deserializar(rutaXMLServidor);

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
