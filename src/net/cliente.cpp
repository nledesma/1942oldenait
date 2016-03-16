#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

class Cliente: public GameSocket{

public:
	Cliente(string ip, int port):GameSocket(){
		inicializar(ip,port);

	}

  void inicializar(string serverAddress ,int port){
    this->setAddress(serverAddress, port);
  }

  void setAddress(string serverAddress, int port){
   		this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
    	this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red

      	this->addr_info.sin_addr.s_addr = inet_addr(serverAddress.c_str()); // Se setea la dirección del server

    	memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
  }

  int conectar(){
    int connected = connect(
      this->socketFd,
      (struct sockaddr *) &this->addr_info,
      sizeof(struct sockaddr_in)
    ); // Me conecto a la direccion.
    if (connected != 0){
      cout << "La conexión falló" << endl;
    }
    return connected;
  }

	string recibir(int longitudMensaje){
		char mensaje[longitudMensaje];
  		int recibidos = 0;
  		cout << "Recibiendo el mensaje... " << endl;

  		// Le envio los bytes al cliente
 	 	while (recibidos < longitudMensaje && recibidos != -1){
    		// Agrego offsets si es que no se envia todo el mensaje
    		recibidos += recv(socketFd, mensaje + recibidos, longitudMensaje - recibidos, 0);
    		if (recibidos == -1){
    			cout << "Error al recibir" << endl;
    		}
    		else{
    		cout << "Recibido " << recibidos << " bytes" << endl;
  			}
  		}

  		mensaje[longitudMensaje - 1] = 0; // Cierro string

  		cout << "Recibo el mensaje: " << mensaje << endl;

  		return string(mensaje);
	}

	/*void cerrar(){
		// socket.shutdown?
  	shutdown(socket->getSocketFd(), 0); // Dejo de transmitir datos

  	//socket.close?
 		 close(socket->getSocketFd()); // Cierro file descriptor
	}*/
};
