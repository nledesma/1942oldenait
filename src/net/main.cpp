#include "gameSocket.cpp"
#include <pthread.h>
#define LOCALHOST "127.0.0.1"
#define PUERTO 8080
#define LONG_MSG 30
#define N_BYTES 50
//#define IP LOCALHOST + ":" + PUERTO

void* inicializarServ(void* arg){
  cout << "Iniciando servidor" << endl;

  GameSocket *gameSocket = new GameSocket();

  gameSocket->inicializarServidor(8080);
  gameSocket->pasivarServidor(20);

  cout << "Esperando conexión..." << endl;
	//Acepto una conexión e ignoro la información de la misma
	int clientFd = accept(gameSocket->getSocketFd(), 0, 0);
	cout << "Conexión aceptada" << endl;

	int bytesSent = 0;

	cout << "Enviando datos" << endl;
	//Le envío 30 bytes al cliente (un número arbitrario)
	while (bytesSent < 40 && bytesSent != -1){
    cout << "ESTO ES ENVIADOS" << bytesSent;
		char message[40] = "MENSAJE\n";
		// Agrego offsets si es que no se envía todo el mensaje
		bytesSent = send(clientFd, message + bytesSent, 40 - bytesSent, MSG_NOSIGNAL);
		cout << "Enviado " << bytesSent << " bytes" << endl;
	}
	cout << "Datos enviados" << endl;

	shutdown(gameSocket->getSocketFd(), 0); //Dejo de transmitir datos
	shutdown(clientFd, 0);

	close(gameSocket->getSocketFd());
	close(clientFd);

	cout << "Gracias, vuelvas prontos" << endl;
  pthread_exit(NULL);
}

void* inicializarCliente(void* arg){
  cout << "Iniciando el cliente en la direccion " << LOCALHOST << endl;
  GameSocket *socket = new GameSocket();
  socket->inicializarCliente(PUERTO, (char*) LOCALHOST);
  socket->conectarCliente();

  char message[LONG_MSG];
  int recibidos = 0;
  cout << "Recibiendo el mensaje... " << endl;

  // Le envio los bytes al cliente
  while (recibidos < LONG_MSG && recibidos != -1){
    cout << "ESTO ES RECIBIDOS: " << recibidos << endl;
    // Agrego offsets si es que no se envia todo el mensaje
    recibidos += recv(socket->getSocketFd(), message + recibidos, LONG_MSG - recibidos, 0);
    cout << "Recibido" << recibidos << "bytes" << endl;
  }

  message[LONG_MSG - 1] = 0; // Cierro string

  cout << "Recibo el mensaje" << message << endl;

  // socket.shutdown?
  shutdown(socket->getSocketFd(), 0); // Dejo de transmitir datos

  //socket.close?
  close(socket->getSocketFd()); // Cierro file descriptor

  cout << "Termina la parte del cliente." << endl;
  pthread_exit(NULL);
}

int main(){
  pthread_t th_cliente, th_servidor;

  // Arranco los threads.
  pthread_create(&th_servidor, NULL, inicializarServ, NULL);
  pthread_create(&th_cliente, NULL, inicializarCliente, NULL);

  // Cierro los threads cuando terminan.
  pthread_join(th_servidor, NULL);
  pthread_join(th_cliente, NULL);

  return 0;
}
