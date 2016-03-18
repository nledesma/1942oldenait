#include "servidorParser.h"

using namespace std;
using namespace tinyxml2;

void ServidorParser::serializar(Servidor * servidor, string ruta) {
	XMLDocument doc;
	
	XMLNode * pRoot = doc.NewElement("servidor");
	pNodo -> InsertFirstChild(pRoot);

	XMLElement * pNodoCantidadMaximaDeClientes = doc.NewElement("cantidadMaximaDeClientes");
	pNodoCantidadMaximaDeClientes -> setText(servidor.getCantidadMaximaDeClientes());

	XMLElement * pNodoPuerto = doc.NewElement("puerto");
	pNodoPuerto -> setText(servidor.getPuerto());

	pRoot -> InsertFirstChild(pNodoCantidadMaximaDeClientes);
	pRoot -> InsertFirstChild(pNodoPuerto);

	XMLError e = doc.SaveFile(ruta);
	if (e != XML_SUCCESS) {
		cout << "Error creando en la ubicación " + ruta << e << endl;
	}
}

Servidor * ServidorParser::deserializar(string ruta) {
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta);

	XMLNode * pRoot = doc.FirstChildElement();
	XMLElement * pElement = pRoot -> FirstChildElement("cantidadMaximaDeClientes");

	int unaCantidadDeClientes;
	eResult = pElement -> QueryIntText(&unaCantidadDeClientes);

	pElement = pRoot -> FirstChildElement("puerto");

	int unPuerto;
	eResult = pElement -> QueryIntText(&unPuerto);

	return new Servidor(unPuerto, unaCantidadDeClientes);
}