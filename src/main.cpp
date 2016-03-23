//#include "gameSocket.hpp"
#include "servidor.hpp"
#include "cliente.hpp"
#include <pthread.h>
#include <string>
#include <iostream>
#define LOCALHOST "127.0.0.1"
#define PUERTO 8080
#define LONG_MSG 30
#define N_BYTES 50
//#define IP LOCALHOST + ":" + PUERTO

Servidor *servidor = new Servidor(8080,3);
Cliente *cliente = new Cliente(LOCALHOST, 8080);

void* fservidor(void* arg){

	//Acepto una conexión e ignoro la información de la misma
	servidor->aceptar();

  string mensajeDePrueba = "HolaEstoEsUnaPrueba\n";
  int longitudDelMensaje = mensajeDePrueba.length();

	servidor->enviarMensaje(mensajeDePrueba,longitudDelMensaje);

  servidor->cerrar();

  pthread_exit(NULL);
}

void* fcliente(void* arg){
  cout << "Iniciando el cliente en la direccion " << LOCALHOST << endl;

  cliente->conectar();

  int caracteresARecibir = 10;
  string mensajeRecibido = cliente->recibir(caracteresARecibir);

  cout << "Mensaje Recibido con exito: " << mensajeRecibido << endl;

  cout << "Termina la parte del cliente." << endl;
  pthread_exit(NULL);
}

int main(){

  cout << "Iniciando servidor" << endl;

  //Por ahora la cantidad de clientes es 3, despues se modificara con el archivo XML.


  //20 es la cantidad de conexiones a encolar
  servidor->pasivar();

  cout << "Esperando conexión..." << endl;

  pthread_t th_cliente, th_servidor;

  // Arranco los threads.
  pthread_create(&th_servidor, NULL, fservidor, NULL);
  pthread_create(&th_cliente, NULL, fcliente, NULL);

  // Cierro los threads cuando terminan.
  pthread_join(th_servidor, NULL);
  pthread_join(th_cliente, NULL);

  return 0;
}
