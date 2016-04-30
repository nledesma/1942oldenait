#include "servidorParser.hpp"

using namespace std;
using namespace tinyxml2;

void ServidorParser::serializar(Servidor * servidor, string ruta) {
	XMLDocument doc;
	//Configuracion
	XMLNode * pConfiguracion = doc.NewElement("configuracion");
	doc.InsertEndChild(pConfiguracion);
	//Servidor
	XMLElement *pServidor = doc.NewElement("servidor");
	doc.InsertEndChild(pServidor);

	XMLElement * pNodoCantidadMaximaDeClientes = doc.NewElement("cantidadMaximaDeClientes");
	(*pNodoCantidadMaximaDeClientes).SetText(servidor -> getCantidadMaximaDeClientes());

	XMLElement * pNodoPuerto = doc.NewElement("puerto");
	(*pNodoPuerto).SetText(servidor -> getPuerto());

	pServidor->InsertEndChild(pNodoCantidadMaximaDeClientes);
	pServidor->InsertEndChild(pNodoPuerto);

	//Escenario
  XMLElement * pNodoEscenario = doc.NewElement("escenario");
	pConfiguracion -> InsertEndChild(pNodoEscenario);
	//Ventana
  XMLElement* pNodoVentana = doc.NewElement("ventana");

	XMLElement * pNodoAncho = doc.NewElement("ancho");
	pNodoAncho-> SetText(servidor -> getEscenario()->getVentana()->getAncho());
	pNodoVentana->InsertEndChild(pNodoAncho);

	XMLElement * pNodoAlto = doc.NewElement("alto");
	pNodoAlto-> SetText(servidor -> getEscenario()->getVentana()->getAlto());
	pNodoVentana->InsertEndChild(pNodoAlto);

	//Avion
	XMLElement *pNodoAvion = doc.NewElement("avion");
	pConfiguracion -> InsertEndChild(pNodoAvion);

	XMLElement * pNodoVelocidadDesplazamiento = doc.NewElement("velocidadDesplazamiento");
	//pNodoVelocidadDesplazamiento -> SetText();
	XMLError e = doc.SaveFile(ruta.c_str());
	if (e != XML_SUCCESS) {
		cout << "Error creando en la ubicación " + ruta << e << endl;
	}
}

Servidor * ServidorParser::deserializar(string ruta) {
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta.c_str());
	XMLNode * pRoot = doc.FirstChildElement();

	//Nodo Servidor
	XMLNode * pNodoServidor = pRoot -> FirstChild();

	int unaCantidadDeClientes;
	XMLNode * pNodoCantidadMaximaDeClientes = pNodoServidor -> FirstChild();
	pNodoCantidadMaximaDeClientes -> ToElement() -> QueryIntText(&unaCantidadDeClientes);

	int unPuerto;
	XMLNode * pNodoPuerto =  pNodoCantidadMaximaDeClientes -> NextSibling();
	pNodoPuerto -> ToElement() -> QueryIntText(&unPuerto);

	//Nodo Escenario
	XMLNode * pNodoEscenario = pRoot -> FirstChild()-> NextSibling();
	//Nodo Ventana
	XMLNode * pNodoVentana = pNodoEscenario -> FirstChild();
	//Ancho
	int ancho;
	XMLNode* pNodoAncho = pNodoVentana->FirstChild();
	pNodoAncho -> ToElement() -> QueryIntText(&ancho);
	//Alto
	int alto;
	XMLNode* pNodoAlto = pNodoVentana->FirstChild()->NextSibling();
	pNodoAlto -> ToElement() -> QueryIntText(&alto);

	return new Servidor(unPuerto, unaCantidadDeClientes);
}
