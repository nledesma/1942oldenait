#ifndef CLIENTE_PARSER_H
#define CLIENTE_PARSER_H

#include "cliente.hpp"
#include "../../../resources/lib/tinyxml2.h"
#include "../../logger/logger.hpp"
#include <sstream>

class ClienteParser {
private:
	bool tipoValido(string valor, int  &tipo);
	bool idValido(list<string> &ids, string id);
	Cliente * cargarConfiguracionPorDefecto();
	//El cliente recibe una direccion IP, un puerto y una coleccion de mensajes de tamaño indefinido
	public:
		void serializador(Cliente *cliente,string ruta);
		Cliente * deserializador(string ruta);
};
#endif // CLIENTE_PARSER_H
