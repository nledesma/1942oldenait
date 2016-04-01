#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include "gameSocket.hpp"
#include "mensaje/mensaje.hpp"
#include "mensaje/fabricaMensajes.hpp"

using namespace std;

GameSocket::GameSocket(){
  // Se inicializa el socket para dominios IPv4, tipo de conexión SOCK_STREAM (TCP), y protocolo a definir
  this->socketFd =  socket(PF_INET, SOCK_STREAM, 0);
}

int GameSocket::enviarBytes(char *pMensaje, int longitudMensaje, int fdReceptor){
	int bytesEnviados = 0;
  int bytesActuales = 0;

	cout << "Enviando datos" << endl;
	while (bytesEnviados < longitudMensaje && bytesActuales != -1){
		// Agrego offsets si es que no se envía todo el mensaje
		bytesActuales = send(fdReceptor, pMensaje + bytesEnviados, longitudMensaje - bytesEnviados, MSG_NOSIGNAL); // Send retorna la cantidad de byes enviados
    bytesEnviados += bytesActuales;
		cout << "Enviado " << bytesEnviados << " bytes" << endl;
	}
	cout << "Datos enviados" << endl;
  if (bytesActuales == - 1 ) {
    Logger::instance()->log("Error al enviar bytes(socket).");
    return -1;
  }
  return MENSAJEOK;
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
    Logger::instance()->log("Error al recibir bytes (socket).");
    return -1;
  } else {
    return MENSAJEOK;
  }
}

void GameSocket::cerrarSocket() {
  shutdown(socketFd, 0); //Dejo de transmitir datos
  close(socketFd);
}

int GameSocket::enviarMensaje(Mensaje * mensaje, int fdReceptor){
  const char * pMensaje = mensaje->codificar();
  return enviarBytes((char*)pMensaje, sizeof(pMensaje), fdReceptor);

}

int GameSocket::recibirMensaje(Mensaje * mensaje, int fdEmisor){
  char pInfoMensaje[LONG_INFO_MENSAJE];
  if (recibirBytes(pInfoMensaje, LONG_INFO_MENSAJE, fdEmisor) == MENSAJEOK){
    infoMensaje datos = Mensaje::decodificarInfo(pInfoMensaje);
    char * pMensaje = new char[datos.longitud];
    if (recibirBytes(pMensaje, datos.longitud, fdEmisor) == MENSAJEOK){
      mensaje = FabricaMensajes::fabricarMensaje(datos, pMensaje);
      delete [] pMensaje;
      return MENSAJEOK;
    } else {
      stringstream ss;
      ss << "Error al recibir bytes del mensaje con id " << datos.id << " de tipo " << datos.tipo;
      cout << ss.str() << endl;
      Logger::instance()->log(ss.str());
      delete [] pMensaje;
    }
  } else {
    Logger::instance()->log("Error al recibir bytes de la cabecera del mensaje.");
  }
  return -1;
}
