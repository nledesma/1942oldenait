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

ClienteParser::ClienteParser(){
	cout << "hola" << endl;
}

void ClienteParser::serializador(Cliente *cliente, string ruta){
	XMLDocument doc;

	// Root
	XMLNode * pCliente = doc.NewElement("cliente");
	doc.InsertEndChild(pCliente);

	XMLElement * pNodoIp = doc.NewElement("ip");
	(*pNodoIp).SetText(cliente->getIP().c_str());

	XMLElement * pNodoPort = doc.NewElement("port");
  // castear a string?
  (*pNodoPort).SetText(cliente->getPort());

	XMLElement * pNodoMensajes = doc.NewElement("mensajes");
  // castear a string?

	// NOTE: hacer la lista de punteros, para que no se copien mensajes, sino punteros.
	for(list<Mensaje*>::iterator iterador = cliente->getMensajes().begin(); iterador != cliente->getMensajes().end(); ++iterador){
		cout << 1 << endl;
		XMLElement * pMensaje = doc.NewElement("mensaje");
		Mensaje *mensaje = *iterador;

		XMLElement * pId = doc.NewElement("id");
		pId-> SetText(mensaje->getId());
		pMensaje ->InsertEndChild(pId);

		XMLElement * pTipo = doc.NewElement("tipo");
		pTipo-> SetText(mensaje->devolverTipo().c_str());
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
			default:{
				cout << "flasheaste" << endl;
				break;
			}
		}

		pMensaje->InsertEndChild(pValor);
		cout << 2 << endl;
		pNodoMensajes -> InsertEndChild(pMensaje);
	}

  // Inserto ambos elementos al root.
  pCliente-> InsertEndChild(pNodoIp);
  pCliente-> InsertEndChild(pNodoPort);
  pCliente-> InsertEndChild(pNodoMensajes);

  XMLError e = doc.SaveFile("cliente.xml");
  if (e != XML_SUCCESS){
    cout << "Error! " << e << endl;
  }
}
