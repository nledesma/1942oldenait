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
	static bool getVentana(XMLElement * pNodoEscenario, int & ancho, int & alto);
	static bool getFondo(XMLElement * pNodoEscenario, string & pathSprite,
		int & ancho, int & alto, float & velocidadY);
	static bool getEscenario(Servidor* servidor, XMLNode* pNodoConfiguracion);
	static bool getElemento(XMLElement * pNodoElemento, string & pathSprite,
		float & posx, float & posy);
	static bool agregarElementos(Servidor* servidor, XMLElement* pNodoEscenario);
	static bool agregarAviones(Servidor* servidor, XMLNode * pNodoConfiguracion);
public:
	static Servidor * deserializar(string ruta);
	static Servidor * deserializarEscenario(string ruta);
	static void serializar(Servidor *servidor, string ruta);
};

#endif
