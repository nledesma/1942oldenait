#ifndef CLIENTE_PARSER_H
#define CLIENTE_PARSER_H

#include "cliente.hpp"

class ClienteParser {
	//El cliente recibe una direccion IP, un puerto y una coleccion de mensajes de tamaño indefinido
	public:
		void serializador(Cliente *cliente,string ruta);
		Cliente deserializador(string ruta);
};
#endif // CLIENTE_PARSER_H
