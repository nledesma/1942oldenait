#ifndef CLIENTE_PARSER_H
#define CLIENTE_PARSER_H

#include "cliente.hpp"
#include "../../accesorios/parserXML.hpp"
#include "../../logger/logger.hpp"
#include <sstream>

#define CONEXIONES_GUARDADAS "../../resources/xml/conexionesCliente.xml"

class ClienteParser : public ParserXML {
private:
	/* utilidades */
	static bool getConexion(XMLElement * pConexion, Conexion & c);
public:
	static list<Conexion> levantarConexiones();

};
#endif // CLIENTE_PARSER_H
