#include "../src/net/servidor/servidorParser.hpp"
#include <string>
#include <pthread.h>

using namespace std;

int main(int argc, char *argv[]){
  /* Se crea el servidor. */
  Servidor * servidor;
  ServidorParser servidorParser;
  servidor = servidorParser.deserializar("servidorPrueba.xml");

  // Servidor aceptando conexiones
  try{
    servidor->pasivar();
  }catch(runtime_error &e){
    Logger::instance()->logError(errno,"Se produjo un error en el listen");
  }

  //servidor->esperar();
  //servidor->cerrar();

  return 0;
}
