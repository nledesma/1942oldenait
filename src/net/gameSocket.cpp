#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include "gameSocket.hpp"
#include "mensaje.hpp"

using namespace std;

GameSocket::GameSocket(){
  // Se inicializa el socket para dominios IPv4, tipo de conexión SOCK_STREAM (TCP), y protocolo a definir
  this->socketFd =  socket(PF_INET, SOCK_STREAM, 0);
}

//TODO ver si conviene pasar mensaje a char* o dejarlo en string.
int GameSocket::enviarBytes(string mensaje, int longitudMensaje, int fdReceptor){
	char *pMensaje = &(mensaje[0]);
	int bytesEnviados = 0;
  int bytesActuales = 0;

	cout << "Enviando datos" << endl;
	while (bytesEnviados < longitudMensaje && bytesActuales != -1){
		// Agrego offsets si es que no se envía todo el mensaje
		bytesActuales = send(fdReceptor, pMensaje + bytesEnviados, longitudMensaje - bytesEnviados, MSG_NOSIGNAL); // Send retorna la cantidad de byes enviados
                                                                                                                // -1 em caso de error. TODO wtf is ERRNO
    bytesEnviados += bytesActuales;
		cout << "Enviado " << bytesEnviados << " bytes" << endl;
	}
	cout << "Datos enviados" << endl;
  if (bytesActuales == - 1 ) return -1 // TODO error.
  return 0;
}

int GameSocket::recibirBytes(char *pMensaje, int longitudMensaje, int fdEmisor){

	int bytesRecibidos = 0;
  int bytesActuales = 0;

	while (bytesRecibidos < longitudMensaje && bytesActuales != -1){
		// Agrego offsets si es que no se envía todo el mensaje
		bytesActuales = recv(fdEmisor, pMensaje + bytesRecibidos, longitudMensaje - bytesRecibidos, 0); // Recv retorna la cantidad de bytes recibidos.

    bytesRecibidos += bytesActuales;
		cout << "recibidos " << bytesRecibidos << " bytes" << endl;
	}
  if (bytesActuales == - 1 ){
    return -1; // TODO error.
  } else {
    return 0;
  }
}

int GameSocket::enviarMensaje(Mensaje * mensaje, int fdReceptor){
  string strMensaje = mensaje->codificar();
  enviarBytes(strMensaje, strMensaje.size(), fdReceptor);
}

int GameSocket::recibirMensaje(Mensaje * mensaje, int fdEmisor){
  char * pInfoMensaje = new char[LONG_INFO_MENSAJE];
  recibirBytes(pInfoMensaje, LONG_INFO_MENSAJE, fdEmisor);
  infoMensaje datos = Mensaje::decodificarInfo();
  delete [] pInfoMensaje;
  char * pMensaje = new char[longitud];
  recibirBytes(pMensaje, longitud, fdEmisor);
  FabricaMensaje::fabricar(datos, mensaje);
}
