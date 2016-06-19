#include "../../resources/lib/tinyxml2.h"
#include "../logger/logger.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace tinyxml2;

class ParserXML {
protected:
    /* Lectores de nodos */
    static bool getString(XMLElement *padre, const char * nombreHijo, string & s);
	static bool getInt(XMLElement *padre, const char* nombreHijo, int & n);
    static bool getFloat(XMLElement *padre, const char* nombreHijo, float & f);
    /* Validaciones generales */
    static bool archivoValido(XMLError eResult, string ruta);
    static bool ipValido(string ip);
    static bool puertoValido(int puerto);
public:
    ParserXML ();
    virtual ~ParserXML ();
};
