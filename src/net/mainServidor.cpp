#include "cliente.hpp"
#include "servidor.hpp"
#include "mensaje.hpp"
#include "ServidorParser.hpp"
#include <string>
#include <pthread>

using namespace std;

void* funcion(void* arg){
  //Acepta la conexion y devuelve el numero del cliente.
    int numeroCliente = servidor->aceptar();

}


int mainServidor(){
  pthread_t threadCliente1, threadCliente2;

  //Se crea el servidor.
  ServidorParser servidorParser;
  Servidor* servidor = servidorParser.deserializar("servidorPrueba.xml");

  //Servidor aceptando conexiones
  servidor->pasivar();

  //Se inicilizan los threads
  pthread_create(&threadCliente1, NULL, funcion, NULL);
  pthread_create(&threadCliente2, NULL, funcion, NULL);

  pthread_join(&threadCliente1, NULL);
  pthread_join(&threadCliente2, NULL);

  return 0;
}
