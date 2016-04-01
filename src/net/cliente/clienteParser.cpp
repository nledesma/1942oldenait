#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
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

	//Conexion
	XMLElement *pConexion = doc.NewElement("conexion");
	doc.InsertEndChild(pConexion);

	// IP del cliente.
	XMLElement * pNodoIp = doc.NewElement("ip");
	(*pNodoIp).SetText(cliente->getIP().c_str());

	// Puerto del cliente.
	XMLElement * pNodoPort = doc.NewElement("port");
  (*pNodoPort).SetText(cliente->getPort());

	pConexion->InsertEndChild(pNodoIp);
	pConexion->InsertEndChild(pNodoPort);
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

  // Inserto Conexion (IP y Puerto) y Lista al xml.
	pCliente->InsertEndChild(pConexion);
	pCliente-> InsertEndChild(pNodoMensajes);

	// Guardado del xml.
  XMLError e = doc.SaveFile(ruta.c_str());
  if (e != XML_SUCCESS){
		// TODO pasar a un log.
    cout << "Error! " << e << endl;
  }
}

// TODO Probablemente debería devolver un puntero a cliente.
Cliente ClienteParser::deserializador(string ruta){
	// TODO Chequear que haya levantado bien! Pasar a un log si hubo error.
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta.c_str());

	if (eResult != XML_NO_ERROR){
		stringstream ss;
		ss << "Error al cargar el mensaje. Código: " << eResult;
		Logger::instance()->log(ss.str());
		doc.LoadFile("resources/xml/clienteDefault.xml");
	}

	XMLNode * pRoot = doc.FirstChild();

	XMLElement * pElement = pRoot -> FirstChildElement("ip");
	string ip = pElement -> GetText();

	pElement = pRoot -> FirstChildElement("port");
	int puerto;
	eResult = pElement -> QueryIntText(&puerto);

	Cliente cliente(ip, puerto);
	FabricaMensajes fabrica;

	XMLElement * pMensajes = pRoot -> FirstChildElement("mensajes");
	XMLElement * pMensaje = pMensajes -> FirstChildElement("mensaje");

	while(pMensaje != NULL){
		int id; string tipo, valor;

		pMensaje -> FirstChildElement("id") -> QueryIntText(&id);
		tipo = pMensaje->FirstChildElement("tipo")->GetText();
		valor = pMensaje->FirstChildElement("valor")->GetText();

		cliente.agregarMensaje(fabrica.fabricarMensaje(id, tipo, valor));

		pMensaje = pMensaje -> NextSiblingElement("mensaje");
	}
	return cliente;
}
