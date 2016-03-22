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
#include "fabricaMensajes.hpp"

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

		// Valor del mensaje.
		XMLElement * pValor = doc.NewElement("valor");
		pValor -> SetText(mensaje->strValor().c_str());
		pMensaje->InsertEndChild(pValor);

		// Agrego el mensaje a la lista en el xml.
		pNodoMensajes->InsertEndChild(pMensaje);
	}

  // Inserto IP, Puerto y Lista al xml.
  pCliente-> InsertEndChild(pNodoIp);
  pCliente-> InsertEndChild(pNodoPort);
  pCliente-> InsertEndChild(pNodoMensajes);

	// Guardado del xml.
  XMLError e = doc.SaveFile(ruta.c_str());
  if (e != XML_SUCCESS){
		// TODO pasar a un log.
    cout << "Error! " << e << endl;
  }
}

Cliente ClienteParser::deserializador(string ruta){
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta.c_str());
	// TODO Chequear que haya levantado bien!
	XMLNode * pRoot = doc.FirstChild();

	XMLElement * pElement = pRoot -> FirstChildElement("ip");

	string ip = pElement -> GetText();

	pElement = pRoot -> FirstChildElement("port");

	int puerto;
	eResult = pElement -> QueryIntText(&puerto);

	Cliente cliente(ip, puerto);

	//TODO MENSAJES.
	XMLElement * pMensajes = pRoot -> FirstChildElement("mensajes");
	XMLElement * pMensaje = pMensajes -> FirstChildElement("mensaje");

	FabricaMensajes fabrica;

	while(pMensaje != NULL){
		//TODO HACER COSAS
		int id; string tipo, valor;

		pMensaje -> FirstChildElement("id") -> QueryIntText(&id);
		tipo = pMensaje->FirstChildElement("tipo")->GetText();
		valor = pMensaje->FirstChildElement("valor")->GetText();

		cliente.agregarMensaje(fabrica.fabricarMensaje(id, tipo, valor));

		pMensaje = pMensaje -> NextSiblingElement("mensaje");
	}

	return cliente;
}
