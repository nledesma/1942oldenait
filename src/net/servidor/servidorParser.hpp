#ifndef SERVIDOR_PARSER_H
#define SERVIDOR_PARSER_H

#include <string>
#include <sstream>
#include "servidor.hpp"
#include "../../../resources/lib/tinyxml2.h"
#include "../../logger.hpp"
using namespace std;

class ServidorParser{
public:
	Servidor * deserializar(string ruta);
	void serializar(Servidor *servidor, string ruta);
};

#endif
