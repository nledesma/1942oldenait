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
	if (eResult != XML_NO_ERROR){
		if(eResult >= 16){
			cout << "El archivo xml provisto no es válido. Se prosigue con la configuración por defecto." << endl;
			Logger::instance()->logWarning("Archivo " + ruta + " invalido. Se prosigue con la configuración por defecto.");
		}else {
			cout << "Ruta inválida. Se prosigue con la configuración por defecto." << endl;
			Logger::instance()->logWarning("Ruta " + ruta + " inválida. Se prosigue con la configuración por defecto.");
		}
		//TODO log Warning!!!!
		return deserializador(DEFAULT_XML);
	}
	XMLNode * pRoot = doc.FirstChild();
	string ip;
	int puerto;
	if(!nodoConexionValido(ip, puerto, pRoot)){
		cout <<"Error en los elementos del archivo xml. Se cargará la configuración por defecto" << endl;
		Logger::instance()->logWarning("Incoveniente en el nodo 'conexion' del xml provisto. Se prosigue con la configuración por defecto.");
		return deserializador(DEFAULT_XML);
	}
	Cliente * cliente = new Cliente(ip, puerto);
	if(!mensajesValidos(cliente, pRoot)){
		cout <<"Error en los elementos del archivo xml. Se cargará la configuración por defecto." << endl;
		Logger::instance()->logWarning("Incoveniente con los mensajes del archivo provisto. Se prosigue con la configuración por defecto.");
		delete cliente;
		return deserializador(DEFAULT_XML);
	}
	return cliente;
}

bool ClienteParser::esIpValido(string ip){
	unsigned int i = 0;
	const char* ipAux = ip.c_str();
	int cantidadPuntos = 0;
	while(i < ip.length()){
		if(ipAux[i] == '.'){
			cantidadPuntos++;
		}
		i++;
	}
	if((cantidadPuntos == 3)&&(ip.length()>=5)){
		return true;
	}
	return false;
}

	bool ClienteParser::mensajesValidos(Cliente * cliente, XMLNode * pRoot) {
		XMLNode * pNodoMensajes = pRoot -> FirstChild()-> NextSibling();
		if(string(pNodoMensajes->Value()) != "mensajes") {
			return false;
		}
		XMLNode * pNodoMensaje = pNodoMensajes -> FirstChild();
		list<string>  ids;
		while(pNodoMensaje != NULL){
			if(string(pNodoMensaje->Value()) != "mensaje"){
				return false;
			}
			string id;
			string tipo, valor;
			XMLNode * pNodoId = pNodoMensaje->FirstChild();
			if(string(pNodoId->Value()) != "id") {
				return false;
			}
			if(pNodoId -> ToElement() -> GetText() == nullptr){
				return false;
			}else{
				id = pNodoId -> ToElement() -> GetText();
			}
			if(!idValido(ids, id)) {
				Logger::instance()->logWarning("Id" + id + " duplicado.");
				return false;
			}
			XMLNode * pNodoTipo = pNodoId -> NextSibling();
			if(string(pNodoTipo->Value()) != "tipo") {
				return false;
			}
			if(pNodoTipo -> ToElement() -> GetText() == nullptr){
				return false;
			}else{
				tipo = pNodoTipo -> ToElement() -> GetText();
			}
			transform(tipo.begin(), tipo.end(),tipo.begin(), ::toupper);
			int codTipo;
			if(!this->tipoValido(tipo, codTipo)){
				return false;
			}
			XMLNode * pNodoValor = pNodoTipo -> NextSibling();
			if (string(pNodoValor->Value()) != "valor") {
				return false;
			}
			if(pNodoValor->ToElement()->GetText() == nullptr){
				return false;
			}else{
				valor = pNodoValor->ToElement()->GetText();
			}
			cliente->agregarMensaje(new Mensaje(codTipo, id, valor));
			pNodoMensaje = pNodoMensaje -> NextSibling();
		}
		return true;
	}

	bool ClienteParser::nodoConexionValido(string &ip, int &puerto, XMLNode * pRoot) {

		XMLNode * pNodoConexion = pRoot -> FirstChild();
		if(string(pNodoConexion->Value()) != "conexion"){
			return false;
		}

		XMLNode * pNodoIp = pNodoConexion -> FirstChild();
		if(string(pNodoIp->Value()) != "IP") {
			return false;
		}

		XMLNode * pNodoPuerto = pNodoIp -> NextSibling();
		if(string(pNodoPuerto->Value()) != "puerto"){
			return false;
		}
		if(pNodoPuerto->NextSibling() != 0){
			return false;
		}
		if(pNodoIp == NULL){
			return false;
		}
		if (pNodoIp->ToElement()->GetText() == nullptr){
			return false;
		} else {
			ip = pNodoIp->ToElement()->GetText();
			if (!esIpValido(ip)) {
				return false;
			}
		}
		if (pNodoPuerto->ToElement()->GetText() == nullptr){
			return false;
		} else{
			pNodoPuerto->ToElement()->QueryIntText(&puerto);
			if ((puerto>=1024)&&(puerto<65535)){
				return true;
			}else{
				return false;
			}
		}
		return true;
}


	bool ClienteParser::idValido(list<string> &ids, string id){
		for(list<string>::iterator it=ids.begin(); it != ids.end(); it++){
			if(it->c_str() == id){
				return false;
			}
		}
		ids.push_back(id);
		return true;
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
