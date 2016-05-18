#ifndef SERVIDOR_PARSER_H
#define SERVIDOR_PARSER_H

#include <string>
#include <sstream>
#include "servidor.hpp"
#include "../../accesorios/parserXML.hpp"
#include "../../logger/logger.hpp"
using namespace std;

class ServidorParser : public ParserXML {
private:
	static bool getCantidadClientes(XMLElement * pNodoServidor, int & nClientes);
	static bool getPuerto(XMLElement * pNodoServidor, int & puerto);
	static bool getServidor(int &unaCantidadDeClientes, int &unPuerto, XMLNode * pRoot);
	static bool nodoEscenarioValido(Servidor* servidor, XMLNode* pNodoConfiguracion);
	static bool nodoElementosValido(Servidor* servidor, XMLNode* pNodoEscenario);
	static bool nodoAvionesValido(Servidor* servidor, XMLNode * pNodoConfiguracion);
	static bool validarContenidoTagInt(XMLNode* pNodoInt, int &unInt);
	static bool validarContenidoTagString(XMLNode* pNodoStr, string &unStr);
	static bool validarContenidoTagFloat(XMLNode* pNodoFloat, float &unFloat);
	static bool archivoValido(XMLError eResult, string ruta);
public:
	static Servidor * deserializar(string ruta);
	static Servidor * deserializarEscenario(string ruta);
	static void serializar(Servidor *servidor, string ruta);
};

#endif
