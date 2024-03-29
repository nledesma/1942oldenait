#ifndef SERVIDOR_PARSER_H
#define SERVIDOR_PARSER_H

#include <string>
#include <sstream>
#include <list>
#include "servidor.hpp"
#include "../../accesorios/parserXML.hpp"
#include "../../logger/logger.hpp"
#include "../../accesorios/powerUpParseado.hpp"
#include "../../accesorios/fabricaPowerUps.hpp"

using namespace std;

class ServidorParser : public ParserXML {
private:
	static bool getCantidadClientes(XMLElement * pNodoServidor, int & nClientes);
	static bool getPuerto(XMLElement * pNodoServidor, int & puerto);
	static bool getServidor(int &unaCantidadDeClientes, int &unPuerto, XMLNode * pRoot);
	static bool getVentana(XMLElement * pNodoEscenario, int & ancho, int & alto);
	static bool getFondo(XMLElement * pNodoEscenario, string & pathSprite,
		int & ancho, int & alto, float & velocidadY);
	static bool getModo(XMLElement * pNodoEscenario, int & modo);
	static bool getEscenario(Servidor* servidor, XMLNode* pNodoConfiguracion);
	static bool getElemento(XMLElement * pNodoElemento, string & pathSprite,
		float & posx, float & posy);
	static bool getEnemigo(XMLElement * pNodoElemento, string &tipo, int &cantidad);
	static bool getPowerUp(XMLElement * pNodoElemento, string &tipo, float &posx, float &posy, int &valor);
	static bool agregarEnemigos(Etapa * etapa, XMLElement* pNodoEtapa, int anchoFondo, int altoFondo,
								int longitudEtapa);
	static bool agregarPowerUps(Etapa * etapa, XMLElement* pNodoEtapa, int anchoFondo, int altoFondo, int longitudEtapa);
	static bool agregarElementos(Etapa* etapa, XMLElement* pNodoEtapa, int altoVentana);
	static bool agregarAviones(Servidor* servidor, XMLNode * pNodoConfiguracion);
	static bool agregarEtapas(EscenarioJuego* escenario, XMLElement * pEscenario);
	static bool getEtapa(XMLElement * pNodoEtapa, Etapa * & etapa, EscenarioJuego* escenario);
public:
	static Servidor * deserializar(string ruta);
	static Servidor * deserializarEscenario(string ruta);
	static void serializar(Servidor *servidor, string ruta);
};

#endif
