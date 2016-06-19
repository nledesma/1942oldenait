#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include "clienteParser.hpp"

using namespace std;
using namespace tinyxml2;

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
		Conexion c;

		if (getConexion(pConexion, c)) {
			conexiones.push_back(c);
		}

		pConexion = pConexion->NextSiblingElement("conexion");
	}

	return conexiones;
}

bool ClienteParser::getConexion(XMLElement * pConexion, Conexion & c) {
	// Tenemos tres nodos en una conexión. Nombre, ip, cliente.
	string nombre;
	string ip;
	int puerto;

	if (!getString(pConexion, "nombre", nombre)){
		Logger::instance()->logWarning("No hay nombre en una conexion.");
		nombre = "Conexion sin nombre"; // Es perdonable que no tenga nombre.
	}

	if (!getString(pConexion, "IP", ip)) {
		Logger::instance()->logWarning("No hay nodo ip. Se ignora una conexion.");
		return false;
	} else if (!ipValido(ip)) {
		Logger::instance()->logWarning("No es válido el ip " + ip + ". Se ignora una conexion.");
		return false;
	}

	if (!getInt(pConexion, "puerto", puerto)){
		Logger::instance()->logWarning("No hay un entero \"puerto\". Se ignora una conexion.");
		return false;
	} else if (!puertoValido(puerto)) {
		stringstream ss;
		ss << "No es válido el puerto " << puerto << ". Se ignora una conexion.";
		Logger::instance()->logWarning(ss.str());
		return false;
	}

	c.nombre = nombre;
	c.ip = ip;
	c.puerto = puerto;

	return true;

}
