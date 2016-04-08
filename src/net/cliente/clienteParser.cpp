#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>
#include "clienteParser.hpp"


#define T_STRING 0
#define T_INT 1
#define T_DOUBLE 2
#define T_CHAR 3
#define DEFAULT_XML "../../resources/xml/clienteDefault.xml"

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
		pId-> SetText(mensaje->getId().c_str());
		pMensaje ->InsertEndChild(pId);

		// Tipo de datos del mensaje.
		XMLElement * pTipo = doc.NewElement("tipo");
		pTipo-> SetText(mensaje->strTipo().c_str());
		pMensaje ->InsertEndChild(pTipo);

		// Valor del mensaje.
		XMLElement * pValor = doc.NewElement("valor");
		pValor -> SetText(mensaje->getValor().c_str());
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
		stringstream ss;
    ss << "Error al guardar cliente. " << e << endl;
		Logger::instance()->logInfo(ss.str());
  }
}

//TODO refactorizar!!!
Cliente * ClienteParser::deserializador(string ruta){
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta.c_str());
	cout <<"Error : "<< eResult << endl;
	if (eResult != XML_NO_ERROR){
		cout << "Error al cargar el mensaje. Código: "<< eResult << endl;
		//TODO log Warning!!!!
		return cargarConfiguracionPorDefecto();
	}

	XMLNode * pRoot = doc.FirstChild();
	XMLNode * pNodeConexion = pRoot -> FirstChild();
	XMLElement * pElement = pNodeConexion -> FirstChildElement("ip");
	string ip = pElement -> GetText();

	pElement = pNodeConexion -> FirstChildElement("port");
	int puerto;
	eResult = pElement -> QueryIntText(&puerto);
	Cliente * cliente = new Cliente(ip, puerto);

	XMLElement * pMensajes = pRoot -> FirstChildElement("mensajes");
	XMLElement * pMensaje = pMensajes -> FirstChildElement("mensaje");
	list<string>  ids;
	while(pMensaje != NULL){
		string id;
		string tipo, valor;
		id = pMensaje -> FirstChildElement("id") -> GetText();
		// if (!idValido(ids, id)) {
			// cout << "Ids repetidos, se utilizará la configuración por defecto" << endl;
			// TODO log warning!!
			// return cargarConfiguracionPorDefecto();
		// }
		tipo = pMensaje->FirstChildElement("tipo")->GetText();
		transform(tipo.begin(), tipo.end(),tipo.begin(), ::toupper);
		int codTipo;
		if(this->tipoValido(tipo, codTipo)){
			cout << "Cod tipo: "<< codTipo << endl;
			valor = pMensaje->FirstChildElement("valor")->GetText();
			cliente->agregarMensaje(new Mensaje(codTipo, id, valor));
		} else {
			cout << " Se intento ingresar un mensaje con un tipo invalido, se utilizará la configuracion por defecto" << endl;
			//TODO log Warning!!!
			return cargarConfiguracionPorDefecto();
		}
		pMensaje = pMensaje -> NextSiblingElement("mensaje");
	}
	return cliente;
}

	bool ClienteParser::tipoValido(string tipo, int &codTipo) {
		if(tipo == "STRING") {
			codTipo = T_STRING;
			return true;
		}
		if(tipo == "INT") {
			codTipo = T_INT;
			return true;
		}
		if(tipo == "DOUBLE") {
			codTipo = T_DOUBLE;
			return true;
		}
		if(tipo == "CHAR") {
			codTipo = T_CHAR;
			return true;
		}
		return false;
	}

	Cliente * ClienteParser::cargarConfiguracionPorDefecto() {
		XMLDocument doc;
		doc.LoadFile(DEFAULT_XML);
		XMLNode * pRoot = doc.FirstChild();

		XMLNode * pNodeConexion = pRoot -> FirstChild();
		XMLElement * pElement = pNodeConexion -> FirstChildElement("ip");
		string ip = pElement -> GetText();

		pElement = pNodeConexion -> FirstChildElement("port");
		int puerto;
		pElement -> QueryIntText(&puerto);

		Cliente * cliente = new Cliente(ip, puerto);

		XMLElement * pMensajes = pRoot -> FirstChildElement("mensajes");
		XMLElement * pMensaje = pMensajes -> FirstChildElement("mensaje");
		while(pMensaje != NULL){
			string id;
			string tipo, valor;
			id = pMensaje -> FirstChildElement("id") -> GetText();
			tipo = pMensaje->FirstChildElement("tipo")->GetText();
			transform(tipo.begin(), tipo.end(),tipo.begin(), ::toupper);
			int codTipo;
			valor = pMensaje->FirstChildElement("valor")->GetText();
			cliente->agregarMensaje(new Mensaje(codTipo, id, valor));
			pMensaje = pMensaje -> NextSiblingElement("mensaje");
		}
		return cliente;
	}

//TODO Falla el iterador, arreglar
	// bool ClienteParser::idValido(list<string> &ids, string id){
	// 	for(list<string>::iterator it=ids.begin(); it != ids.end(); it++){
	// 		if(&it.c_str() == id){
	// 			return false;
	// 		}
	// 	}
	// 	ids.push_back(id);
	// 	return true;
	// }
