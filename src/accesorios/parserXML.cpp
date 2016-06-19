#include "parserXML.hpp"

/* Lectores */
bool ParserXML::getString(XMLElement * padre, const char * nombreHijo, string & s) {
	// Hay que hacer delete de esto?
	XMLElement * pHijo = padre->FirstChildElement(nombreHijo);
	if (!pHijo) return false;

	const char * texto = pHijo->GetText();
	if (!texto) {
		return false;
	}

	s = string(texto);
	return true;
}

// TODO Logguear en lugar de cout.
bool ParserXML::getInt(XMLElement * padre, const char * nombreHijo, int & n) {
	XMLElement * pHijo = padre->FirstChildElement(nombreHijo);
	if (!pHijo) {
		cout << "No existe el tag" << nombreHijo << "." << endl;
		return false;
	}

	XMLError e = pHijo->QueryIntText(&n);
	if (e == XML_CAN_NOT_CONVERT_TEXT) {
		cout << "La tag no contiene un entero." << endl;
		return false;
	} else if (e == XML_NO_TEXT_NODE) {
		cout << "La tag no contiene texto." << endl;
		return false;
	}
	return true;
}

bool ParserXML::getFloat(XMLElement * padre, const char * nombreHijo, float& f) {
	XMLElement * pHijo = padre->FirstChildElement(nombreHijo);
	if (!pHijo) {
		cout << "No existe el tag" << nombreHijo << "." << endl;
		return false;
	}

	XMLError e = pHijo->QueryFloatText(&f);
	if (e == XML_CAN_NOT_CONVERT_TEXT) {
		cout << "La tag no contiene un flotante." << endl;
		return false;
	} else if (e == XML_NO_TEXT_NODE) {
		cout << "La tag no contiene texto." << endl;
		return false;
	}
	return true;
}

/* Validaciones Generales */

bool ParserXML::archivoValido(XMLError eResult, string ruta){
	if (eResult != XML_NO_ERROR){
		if(eResult >= 16){
			cout << "El archivo" + ruta +"  no es válido" << endl;
			Logger::instance()->logWarning("Archivo " + ruta + " invalido.");
		} else if (eResult == XML_ERROR_PARSING_ELEMENT || eResult == XML_ERROR_ELEMENT_MISMATCH || eResult == XML_ERROR_IDENTIFYING_TAG) {
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

bool ParserXML::ipValido(string ip){
	// NOTE debe haber una función que cuenta apariciones de un caracter en una string.
	int cantidadPuntos = 0;

	for (unsigned int i = 0; i < ip.length(); i++){
		if (ip[i] == '.') cantidadPuntos ++;
	}
	// TODO esto debería validar que entre puntos haya números entre 0 y 255.
	return cantidadPuntos == 3 && ip.length() >= 5;
}

bool ParserXML::puertoValido(int puerto) {
	return puerto >= 1024 && puerto < 65535;
}
