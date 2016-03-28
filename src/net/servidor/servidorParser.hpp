#ifndef SERVIDOR_PARSER_H
#define SERVIDOR_PARSER_H

#include <string>
#include "servidor.hpp"
#include "../../../resources/lib/tinyxml2.h"

using namespace std;

class ServidorParser{
public:
	Servidor * deserializar(string ruta);
	void serializar(Servidor *servidor, string ruta);
};

#endif