#include "../src/net/servidor/servidorParser.hpp"
#include <string>
#include <pthread.h>

#define DEFAULT_XML "../../resources/xml/servidorDefault.xml"

using namespace std;

int main(int argc, char *argv[]){

  string rutaXMLServidor;

  if (argc < 2){
    cout << "Argumentos insuficientes, se utilizará el XML por defecto" << endl;
    Logger::instance()->logWarning("No se ingresó la cantidad de parámetros suficientes. Se inicializa el servidor con el XML por defecto");
    rutaXMLServidor = (DEFAULT_XML);
  } else {
    rutaXMLServidor = argv[1];
  }  
    /* Se crea el servidor. */
    Servidor * servidor;
    ServidorParser servidorParser;
    servidor = servidorParser.deserializar(rutaXMLServidor);
  
    // Servidor aceptando conexiones
    try{
      servidor->pasivar();
    }catch(runtime_error &e){
      Logger::instance()->logError(errno,"Se produjo un error en el listen");
    }
  
    //servidor->esperar();
    //servidor->cerrar();
  
    pthread_exit(NULL);
}