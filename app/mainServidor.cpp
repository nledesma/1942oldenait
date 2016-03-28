#include "../src/net/cliente/cliente.hpp"
#include "../src/net/mensaje/mensaje.hpp"
#include "../src/net/servidor/servidorParser.hpp"
#include <string>
#include <pthread.h>

using namespace std;
void* funcion(void* arg){
  cout << "ESTO ES UN CLIENTE" << endl;
  //Cada cliente se conecta al servidor.
  Cliente* pcliente = (Cliente*)arg;
  pcliente->conectar();
  pthread_exit(NULL);
}

int main(){
  Servidor * servidor;
  pthread_t threadCliente1, threadCliente2;
  Cliente cliente1("127.0.0.1", 8080);
  Cliente cliente2("127.0.0.1", 8080);
  // Se crea el servidor.
  ServidorParser servidorParser;
  servidor = servidorParser.deserializar("servidorPrueba.xml");

  // Servidor aceptando conexiones
  servidor->pasivar();
  // Se iniciliazan los threads
  pthread_create(&threadCliente1, NULL, funcion, &cliente1);
  pthread_create(&threadCliente2, NULL, funcion, &cliente2);


  pthread_join(threadCliente1, NULL);
  pthread_join(threadCliente2, NULL);
  servidor->esperar();

  return 0;
}
