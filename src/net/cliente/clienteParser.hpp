#ifndef CLIENTE_PARSER_H
#define CLIENTE_PARSER_H

#include "cliente.hpp"
#include "../../../resources/lib/tinyxml2.h"
#include "../../logger/logger.hpp"
#include <sstream>

#define CONEXIONES_GUARDADAS "../../resources/xml/conexionesCliente.xml"

using namespace tinyxml2;

class ClienteParser {
private:
	/* utilidades */
	static string getString(XMLElement *padre, const char * nombreHijo);
	static int getInt(XMLElement *padre, const char* nombreHijo);
	static bool nodoConexionValido(string &ip, int &puerto, XMLNode * pRoot);
	static bool esIpValido(string ip);
public:
	static void serializador(Cliente *cliente, string ruta);
	static Cliente * deserializador(string ruta);
	static list<Conexion> levantarConexiones();
	static bool archivoValido(XMLError eResult, string ruta);

};
#endif // CLIENTE_PARSER_H
