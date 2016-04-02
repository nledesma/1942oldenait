#include "../src/net/cliente/cliente.hpp"
#include "../src/net/mensaje/mensaje.hpp"
#include "../src/net/servidor/servidorParser.hpp"
#include <string>
#include <pthread.h>

using namespace std;


int main(int argc, char *argv[]){
  /* Se crea el servidor. */
  Servidor * servidor;
  ServidorParser servidorParser;

  /* Se carga obtiene el puerto y la cantidad máxima *
   * de clientes a partir de un archivo '.xml'.      */
  if (argc != 0){
    servidor = servidorParser.deserializar(argv[0]);
  } else {
    servidor = servidorParser.deserializar("servidorPrueba.xml");
  }

  // Servidor aceptando conexiones
  servidor->pasivar();
  servidor->esperar();
  servidor->cerrar();
}
