#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <list>

using namespace std;

class Servidor: public GameSocket{
private:
	list <int> clientes;
public:
	Servidor(int port, int cantidadDeClientes):GameSocket(){
		inicializar(port);
	}


	void inicializar(int port){
		this->setAddress(port); // Se setea el puerto en addr_info
		bind(this->socketFd, (struct sockaddr*) &this->addr_info, sizeof(struct sockaddr_in)); // Se vincula el socket al puerto indicado en addr_info
	}

	void setAddress(int port){
   		this->addr_info.sin_family = AF_INET; // Se setea la familia de direcciones IPv4
    	this->addr_info.sin_port = htons(port); // Se setea el puerto en formato corto de red

      	this->addr_info.sin_addr.s_addr = INADDR_ANY; // El socket se puede asociar a cualquier conexión

    	memset(this->addr_info.sin_zero, 0, sizeof(this->addr_info.sin_zero));
  	}

	void pasivar(int backlog){
    	listen(this->socketFd, backlog);
  	}

  	//Agrega el nuevo cliente a la lista de clientes para aceptarlo.
  	void aceptar(){

  		clientes.push_back(accept(socketFd, 0, 0));

		cout << "Conexión aceptada" << endl;

  	}

 	void enviarMensaje(string mensaje, int longitudMensaje){

  		char *pMensaje = &(mensaje[0]);
 		int bytesSent = 0;

		cout << "Enviando datos" << endl;
		while (bytesSent < longitudMensaje && bytesSent != -1){
			// Agrego offsets si es que no se envía todo el mensaje
			bytesSent = send(clientes.front(), pMensaje + bytesSent, longitudMensaje - bytesSent, MSG_NOSIGNAL);
			cout << "Enviado " << bytesSent << " bytes" << endl;
		}
		cout << "Datos enviados" << endl;

	}

	void cerrar(){
		for(list<int>::iterator iterador = clientes.begin(); iterador != clientes.end(); iterador++){
			int clienteActual = *iterador;
				shutdown(clienteActual, 0);
				close(clienteActual);
		}
		shutdown(socketFd, 0); //Dejo de transmitir datos
		close(socketFd);

		cout << "Servidor cerrado" << endl;

	}

};
