#ifndef SERVIDOR_PARSER_H
#define SERVIDOR_PARSER_H

#include <string>
#include <sstream>
#include "servidor.hpp"
#include "tinyxml2.h"
#include "logger.hpp"
#include <iterator>

using namespace std;
using namespace tinyxml2;

class ServidorParser{
public:
	Servidor * deserializar(string ruta);
	void serializar(Servidor *servidor, string ruta);
};

#endif
