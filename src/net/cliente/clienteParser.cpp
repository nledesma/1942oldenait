#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include "clienteParser.hpp"

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

  // Inserto Conexion (IP y Puerto) y Lista al xml.
	pCliente->InsertEndChild(pConexion);

	// Guardado del xml.
  XMLError e = doc.SaveFile(ruta.c_str());
  if (e != XML_SUCCESS){
		stringstream ss;
    ss << "Error al guardar cliente. " << e << endl;
		Logger::instance()->logInfo(ss.str());
  }
}

// Por ahora siempre levanta del archivo de conexiones.
// NOTE Por ahí convendría una lista de punteros a conexiones... y devolver un puntero...
list<Conexion> ClienteParser::levantarConexiones(){
	XMLDocument doc;
	list<Conexion> conexiones;

	XMLError eResult = doc.LoadFile(CONEXIONES_GUARDADAS);
	// Si hay error devuelve la lista vacía.
	if (!archivoValido(eResult, CONEXIONES_GUARDADAS)) return conexiones;

	XMLNode * pRoot = doc.FirstChild();

	// Itero sobre las conexiones.
	XMLElement * pConexion = pRoot->FirstChildElement("conexion");
	while(pConexion != NULL) {

		Conexion c = {
			.nombre = getString(pConexion, "nombre"),
			.ip = getString(pConexion, "IP"),
			.puerto = getInt(pConexion, "puerto")
		};
		conexiones.push_back(c);

		pConexion = pConexion->NextSiblingElement("conexion");
	}

	return conexiones;
}

string ClienteParser::getString(XMLElement * padre, const char * nombreHijo){
	// Hay que hacer delete de esto?
	XMLElement * pHijo = padre->FirstChildElement(nombreHijo);
	string texto(pHijo->GetText());
	return texto;
}

int ClienteParser::getInt(XMLElement * padre, const char * nombreHijo){
	XMLElement * pHijo = padre->FirstChildElement(nombreHijo);
	int n;
	pHijo->QueryIntText(&n);
	return n;
}


bool ClienteParser::archivoValido(XMLError eResult, string ruta){
	if (eResult != XML_NO_ERROR){
		if(eResult >= 16){
			cout << "El archivo" + ruta +"  no es válido" << endl;
			Logger::instance()->logWarning("Archivo " + ruta + " invalido.");
		}else if (eResult == XML_ERROR_PARSING_ELEMENT || eResult == XML_ERROR_ELEMENT_MISMATCH || eResult == XML_ERROR_IDENTIFYING_TAG) {
			cout << "El archivo " + ruta + " está malformado." << endl;
			Logger::instance()->logWarning("El archivo " + ruta + " está malformado.");
		} else if (eResult == XML_ERROR_FILE_COULD_NOT_BE_OPENED || eResult == XML_ERROR_FILE_READ_ERROR) {
			cout << "El archivo " + ruta + " está malformado." << endl;
			Logger::instance()->logWarning("El archivo " + ruta + " está malformado.");
		} else if (eResult == XML_ERROR_FILE_NOT_FOUND){
			cout << "Ruta " + ruta + " inválida." << endl;
			Logger::instance()->logWarning("Ruta " + ruta + " inválida.");
		}

		return false;
	}
	return true;
}

Cliente * ClienteParser::deserializador(string ruta){
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta.c_str());
	if (!archivoValido(eResult, ruta)) return NULL;

	XMLNode * pRoot = doc.FirstChild();
	string ip;
	int puerto;
	if(!nodoConexionValido(ip, puerto, pRoot)){
		cout <<"Error en los elementos del archivo " + ruta  << endl;
		Logger::instance()->logWarning("Incoveniente en el nodo 'conexion' del archivo " + ruta);
		return NULL;
	}
	Cliente * cliente = new Cliente(ip, puerto);

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



bool ClienteParser::nodoConexionValido(string &ip, int &puerto, XMLNode * pRoot) {

	XMLNode * pNodoConexion = pRoot -> FirstChild();
	if((pNodoConexion == 0) || (string(pNodoConexion->Value()) != "conexion")){
		return false;
	}

	XMLNode * pNodoIp = pNodoConexion -> FirstChild();
	if((pNodoIp == 0) || (string(pNodoIp->Value()) != "IP")) {
		return false;
	}

	XMLNode * pNodoPuerto = pNodoIp -> NextSibling();
	if((pNodoPuerto == 0) || (string(pNodoPuerto->Value()) != "puerto")){
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
