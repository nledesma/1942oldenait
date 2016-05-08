#ifndef SERVIDOR_PARSER_H
#define SERVIDOR_PARSER_H

#include <string>
#include <sstream>
#include "servidor.hpp"
#include "../../../resources/lib/tinyxml2.h"
#include "../../logger/logger.hpp"
using namespace std;
using namespace tinyxml2;

class ServidorParser{
private:
	bool laCantidadEsValida(XMLNode * pNodoCantidadClientes, int &cantidadDeClientes);
	bool elPuertoEsValido(XMLNode * pNodoPuerto, int &unPuerto);
	bool nodoServidorValido(int &unaCantidadDeClientes, int &unPuerto, XMLNode * pRoot);
public:
	Servidor * deserializar(string ruta);
	Servidor * deserializarEscenario(string ruta);
	void serializar(Servidor *servidor, string ruta);
};

#endif
