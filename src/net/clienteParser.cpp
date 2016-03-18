#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "cliente.cpp"
#include <list>
#include <iterator>

using namespace std;
using namespace tinyxml2;

class ClienteParser {
	//El cliente recibe una direccion IP, un puerto y una coleccion de mensajes de tamaño indefinido
	public: void serializador(Cliente *cliente,string ruta);
	public: Cliente deserializador(string ruta);
};

void ClienteParser::serializador(Cliente *cliente, string ruta){
	XMLDocument doc;

	// Root
	XMLNode * pRoot = doc.NewElement("Cliente");
	doc.InsertFirstChild(pRoot);

	// Hijos del root. TODO: diferencia entre element y node.
	XMLElement * pNodoIp = doc.NewElement("ip");
	(*pNodoIp).SetText(10);

	XMLElement * pNodoPort = doc.NewElement("port");
  // castear a string?
  (*pNodoPort).SetText(10);

	XMLElement * pNodoMensajes = doc.NewElement("mensajes");
  // castear a string?

	// NOTE: hacer la lista de punteros, para que no se copien mensajes, sino punteros.
	for(list<Mensaje>::iterator iterador = cliente->getMensajes().begin(); iterador != cliente->getMensajes().end(); iterador++){
		Mensaje mensaje = (*iterador);

		XMLElement * pListaMensajes = doc.NewElement("mensaje");
		pListaMensajes-> SetText(mensaje);

		XMLElement * pListaMensajes = doc.NewElement("id");
		pListaMensajes-> SetText(mensaje.getId());

		XMLElement * pListaMensajes = doc.NewElement("tipo");
		pListaMensajes-> SetText(mensaje.getTipo());


		XMLElement * pListaMensajes = doc.NewElement("valor");
		// TODO ¿Quién debería encargarse de esto?
		switch (mensaje.getTipo()) {
			case T_STRING:{
				string valor = (string) (*mensaje.getValor());
				pListaMensajes-> SetText(valor);
				break;
			}
			case T_INT:{
				int valor = (int) (*mensaje.getValor());
				pListaMensajes-> SetText(valor);
				break;
			}
			case T_DOUBLE:{
				double valor = (double) (*mensaje.getValor());
				pListaMensajes-> SetText(valor);
				break;
				}
			case T_CHAR:{
				char valor = (char) (*mensaje.getValor());
				pListaMensajes-> SetText(valor);
				break;
			}
		}

		pMensaje->InsertEndChild(pListaMensajes);
		}
	}

    (*pNodoMensajes).SetText(10);

    // Inserto ambos elementos al root.
    pRoot -> InsertFirstChild(pNodoIp);
    pRoot -> InsertFirstChild(pNodoPort);
    pRoot -> InsertFirstChild(pNodoMensajes);

    XMLError e = doc.SaveFile("cliente.xml");
    if (e != XML_SUCCESS){
	    cout << "Error! " << e << endl;
    }
}
