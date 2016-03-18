#ifndef CLIENTE_PARSER_H
#define CLIENTE_PARSER_H

#include "tinyxml2.h"
#include "cliente.hpp"
#include <list>

class ClienteParser {
	//El cliente recibe una direccion IP, un puerto y una coleccion de mensajes de tamaño indefinido
	public:
		ClienteParser();
		void serializador(Cliente *cliente,string ruta);
		Cliente deserializador(string ruta);
};
#endif // CLIENTE_PARSER_H