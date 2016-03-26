#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include "gameSocket.hpp"

using namespace std;

GameSocket::GameSocket(){
  // Se inicializa el socket para dominios IPv4, tipo de conexión SOCK_STREAM (TCP), y protocolo a definir
  this->socketFd =  socket(PF_INET, SOCK_STREAM, 0);
}

//TODO ver si conviene pasar mensaje a char* o dejarlo en string.
void GameSocket::enviarBytes(string mensaje, int longitudMensaje){
	char *pMensaje = &(mensaje[0]);
	int bytesEnviados = 0;

	cout << "Enviando datos" << endl;
	while (bytesEnviados < longitudMensaje && bytesEnviados != -1){
		// Agrego offsets si es que no se envía todo el mensaje
		bytesEnviados += send(clientes.front(), pMensaje + bytesEnviados, longitudMensaje - bytesEnviados, MSG_NOSIGNAL);
		cout << "Enviado " << bytesEnviados << " bytes" << endl;
	}
	cout << "Datos enviados" << endl;
}

void GameSocket::recibirBytes(string mensaje, int longitudMensaje){
	char *pMensaje = &(mensaje[0]);
	int bytesRecibidos = 0;

	while (bytesRecibidos < longitudMensaje && bytesRecibidos != -1){
		// Agrego offsets si es que no se envía todo el mensaje
		bytesRecibidos += recv(clientes.front(), pMensaje + bytesRecibidos, longitudMensaje - bytesRecibidos, 0);
		cout << "recibidos " << bytesRecibidos << " bytes" << endl;
	}
}
