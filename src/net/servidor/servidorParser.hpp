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
	bool nodoEscenarioValido(Servidor* servidor, XMLNode* pNodoConfiguracion);
	bool nodoElementosValido(Servidor* servidor, XMLNode* pNodoEscenario);
	bool nodoAvionesValido(Servidor* servidor, XMLNode * pNodoConfiguracion);
	bool validarContenidoTagInt(XMLNode* pNodoInt, int &unInt);
	bool validarContenidoTagString(XMLNode* pNodoStr, string &unStr);
	bool validarContenidoTagFloat(XMLNode* pNodoFloat, float &unFloat);
	bool archivoValido(XMLError eResult, string ruta);
public:
	Servidor * deserializar(string ruta);
	Servidor * deserializarEscenario(string ruta);
	void serializar(Servidor *servidor, string ruta);
};

#endif
