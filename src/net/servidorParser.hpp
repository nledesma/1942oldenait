#ifndef SERVIDOR_PARSER_H
#define SERVIDOR_PARSER_H

#include <string>
#include "servidor.cpp"

using namespace std;

class ServidorParser{
public:
	Servidor * deserializar(string ruta);
	void serializar(Servidor *servidor, string ruta);
};

#endif
