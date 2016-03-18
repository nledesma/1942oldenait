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
	XMLNode * pCliente = doc.NewElement("cliente");
	doc.InsertFirstChild(pCliente);

	// Hijos del root. TODO: diferencia entre element y node.
	XMLElement * pNodoIp = doc.NewElement("ip");
	(*pNodoIp).SetText(10);

	XMLElement * pNodoPort = doc.NewElement("port");
  // castear a string?
  (*pNodoPort).SetText(10);

	XMLElement * pNodoMensajes = doc.NewElement("mensajes");
  // castear a string?

	// NOTE: hacer la lista de punteros, para que no se copien mensajes, sino punteros.
	for(list<Mensaje*>::iterator iterador = cliente->getMensajes().begin(); iterador != cliente->getMensajes().end(); iterador++){
		XMLElement * pMensaje = doc.NewElement("mensaje");
		Mensaje *mensaje =  (*iterador);

		XMLElement * pId = doc.NewElement("id");
		pId-> SetText(mensaje->getId());
		pMensaje ->InsertEndChild(pId);

		XMLElement * pTipo = doc.NewElement("tipo");
		pTipo-> SetText(mensaje->getTipo());
		pMensaje ->InsertEndChild(pTipo);

		XMLElement * pValor = doc.NewElement("valor");
		// TODO ¿Quién debería encargarse de esto?
		switch (mensaje->getTipo()) {
			case T_STRING:{
				string valor = *((string*) mensaje->getValor());
				pValor-> SetText(valor.c_str());
				break;
			}
			case T_INT:{
				int valor = *((int*) mensaje->getValor());
				pValor-> SetText(valor);
				break;
			}
			case T_DOUBLE:{
				double valor = *((double*) mensaje->getValor());
				pValor-> SetText(valor);
				break;
				}
			case T_CHAR:{
				char valor = *((char*) mensaje->getValor());
				pValor-> SetText(valor);
				break;
			}
		}

		pMensaje->InsertEndChild(pValor);
	}

  // Inserto ambos elementos al root.
  pCliente-> InsertFirstChild(pNodoIp);
  pCliente-> InsertFirstChild(pNodoPort);
  pCliente-> InsertFirstChild(pNodoMensajes);

  XMLError e = doc.SaveFile("cliente.xml");
  if (e != XML_SUCCESS){
    cout << "Error! " << e << endl;
  }
}
