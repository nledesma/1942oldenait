#include "servidorParser.hpp"

#define DEFAULT_XML "../../resources/xml/servidorDefault.xml"

using namespace std;
using namespace tinyxml2;

void ServidorParser::serializar(Servidor * servidor, string ruta) {
	XMLDocument doc;

	XMLNode * pRoot = doc.NewElement("servidor");
	pRoot -> InsertFirstChild(pRoot);

	XMLElement * pNodoCantidadMaximaDeClientes = doc.NewElement("cantidadMaximaDeClientes");
	(*pNodoCantidadMaximaDeClientes).SetText(servidor -> getCantidadMaximaDeClientes());

	XMLElement * pNodoPuerto = doc.NewElement("puerto");
	(*pNodoPuerto).SetText(servidor -> getPuerto());

	pRoot -> InsertFirstChild(pNodoCantidadMaximaDeClientes);
	pRoot -> InsertFirstChild(pNodoPuerto);

	XMLError e = doc.SaveFile(ruta.c_str());
	if (e != XML_SUCCESS) {
		cout << "Error creando en la ubicación " + ruta << e << endl;
	}
}

Servidor * ServidorParser::deserializar(string ruta) {
	XMLDocument doc;
		XMLError eResult = doc.LoadFile(ruta.c_str());
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
			return NULL;
		}


		XMLNode * pRoot = doc.FirstChildElement();
		XMLNode * pNodoCantidadMaximaDeClientes = pRoot -> FirstChild();
		int cantidadMaximaDeClientes;
		if((pNodoCantidadMaximaDeClientes == 0) || (string(pNodoCantidadMaximaDeClientes -> Value()) != "cantidadMaximaDeClientes") || (!laCantidadEsValida(pNodoCantidadMaximaDeClientes, cantidadMaximaDeClientes))) {
			cout <<"Error en los elementos del archivo " + ruta  << endl;
			Logger::instance()->logWarning("Incoveniente en la cantidad de clientes del archivo " + ruta);
			Logger::instance()->logInfo("Se procede a cargar el archivo por defecto");
			return NULL;
		}

		XMLNode * pNodoPuerto =  pNodoCantidadMaximaDeClientes -> NextSibling();

		int unPuerto;

		if((pNodoPuerto == 0) || (string(pNodoPuerto -> Value()) != "puerto") || (!elPuertoEsValido(pNodoPuerto, unPuerto))) {
			cout <<"Error en los elementos del archivo " + ruta  << endl;
			Logger::instance()->logWarning("Incoveniente en el puerto del archivo " + ruta);
			Logger::instance()->logInfo("Se procede a cargar el archivo por defecto");
			return NULL;
		}
		Servidor* servidor = new Servidor(unPuerto, cantidadMaximaDeClientes);
		return servidor;
	}

	bool ServidorParser::elPuertoEsValido(XMLNode * pNodoPuerto, int &unPuerto) {
		if (!(pNodoPuerto->ToElement()->GetText() == nullptr)) {
				pNodoPuerto ->ToElement() -> QueryIntText(&unPuerto);
				return((unPuerto>=1024)&&(unPuerto<65535));
		} else {
			return false;
		}
	}

	bool ServidorParser::laCantidadEsValida(XMLNode * pNodoCantidadClientes, int &cantidadDeClientes) {
		if(!(pNodoCantidadClientes -> ToElement() -> GetText() == nullptr)) {
			pNodoCantidadClientes -> ToElement() -> QueryIntText(&cantidadDeClientes);
			return(cantidadDeClientes > 0);
		} else {
			return false;
		}
	}
