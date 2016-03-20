#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "cliente.hpp"
#include <list>
#include <iterator>
#include "clienteParser.hpp"

#define T_STRING 0
#define T_INT 1
#define T_DOUBLE 2
#define T_CHAR 3

using namespace std;
using namespace tinyxml2;

void ClienteParser::serializador(Cliente *cliente, string ruta){
	XMLDocument doc;

	// Cliente (root)
	XMLNode * pCliente = doc.NewElement("cliente");
	doc.InsertEndChild(pCliente);

	// IP del cliente.
	XMLElement * pNodoIp = doc.NewElement("ip");
	(*pNodoIp).SetText(cliente->getIP().c_str());

	// Puerto del cliente.
	XMLElement * pNodoPort = doc.NewElement("port");
  (*pNodoPort).SetText(cliente->getPort());

	// Lista de mensajes.
	XMLElement * pNodoMensajes = doc.NewElement("mensajes");

	for(list<Mensaje*>::iterator iterador = cliente->getMensajes().begin(); iterador != cliente->getMensajes().end(); ++iterador){
		XMLElement * pMensaje = doc.NewElement("mensaje");
		Mensaje *mensaje = *iterador;

		// ID del mensaje.
		XMLElement * pId = doc.NewElement("id");
		pId-> SetText(mensaje->getId());
		pMensaje ->InsertEndChild(pId);

		// Tipo de datos del mensaje.
		XMLElement * pTipo = doc.NewElement("tipo");
		pTipo-> SetText(mensaje->strTipo().c_str());
		pMensaje ->InsertEndChild(pTipo);

		XMLElement * pValor = doc.NewElement("valor");
		// TODO ¿Quién debería encargarse de esto? ¿Herencia de mensajes?
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
				char arr[] = {valor , '\0'};
				pValor-> SetText(arr);
				break;
			}
			default:{
				// TODO pasar a un log.
				cout << "Tipo " << mensaje->getTipo() << " no válido." << endl;
				break;
			}
		}

		// Valor del mensaje.
		pMensaje->InsertEndChild(pValor);
		// Agrego el mensaje a la lista en el xml.
		pNodoMensajes->InsertEndChild(pMensaje);
	}

  // Inserto IP, Puerto y Lista al xml.
  pCliente-> InsertEndChild(pNodoIp);
  pCliente-> InsertEndChild(pNodoPort);
  pCliente-> InsertEndChild(pNodoMensajes);

	// Guardado del xml.
  XMLError e = doc.SaveFile("cliente.xml");
  if (e != XML_SUCCESS){
		// TODO pasar a un log.
    cout << "Error! " << e << endl;
  }
}
