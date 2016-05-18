#include "servidorParser.hpp"

void ServidorParser::serializar(Servidor * servidor, string ruta) {
	XMLDocument doc;

	XMLNode * pRoot = doc.NewElement("servidor");
	pRoot -> InsertFirstChild(pRoot);

	XMLElement * pNodoCantidadMaximaDeClientes = doc.NewElement("cantidadMaximaDeClientes");
	(*pNodoCantidadMaximaDeClientes).SetText(servidor -> getCantidadMaximaDeClientes());

	XMLElement * pNodoPuerto = doc.NewElement("puerto");
	(*pNodoPuerto).SetText(servidor -> getPuerto());

	pRoot -> InsertFirstChild(pNodoCantidadMaximaDeClientes);
	pRoot -> InsertFirstChild(pNodoPuerto);

	XMLError e = doc.SaveFile(ruta.c_str());
	if (e != XML_SUCCESS) {
		cout << "Error creando en la ubicación " + ruta << e << endl;
	}
}

bool ServidorParser::getPuerto(XMLElement * pNodoServidor, int & puerto) {
	if (!getInt(pNodoServidor,"puerto", puerto)) return false;
	if (!puertoValido(puerto)) return false;
	return true;
}

bool ServidorParser::getCantidadClientes(XMLElement * pNodoServidor, int &nClientes) {
	if (!getInt(pNodoServidor, "cantidadMaximaDeClientes", nClientes))
		return false;

	if (nClientes < 1 || nClientes > 4) {
		Logger::instance()->logWarning("Cantidad de clientes no valida.");
		return false;
	}

	return true;
}

bool ServidorParser::getServidor(int & cantidadClientes, int &puerto, XMLNode *pRoot){
	XMLElement * pNodoServidor = pRoot -> FirstChildElement("servidor");
	if (!pNodoServidor) return false;

	// Cantidad Maxima de Clientes
	if (!getCantidadClientes(pNodoServidor, cantidadClientes)) return false;

	// Puerto
	if (!getPuerto(pNodoServidor, puerto)) return false;

	return true;
}

bool ServidorParser::getVentana(XMLElement * pNodoEscenario, int & ancho, int & alto) {
	// TODO loguear si hay problemas.
	XMLElement * pVentana = pNodoEscenario->FirstChildElement("ventana");
	if (!pVentana) return false;

	if (!getInt(pVentana, "ancho", ancho)) return false;
	if (!getInt(pVentana, "alto", alto)) return false;
	return true;
}

bool ServidorParser::getFondo(XMLElement * pNodoEscenario, string & spriteId, int & ancho, int & alto, float & velocidadY) {
	XMLElement * pFondo = pNodoEscenario->FirstChildElement("fondo");
	if (!pFondo) return false;

	if (!getString(pFondo, "spriteIdFondo", spriteId)) spriteId = "";
	if (!getInt(pFondo, "ancho", ancho)) return false;
	if (!getInt(pFondo, "alto", alto)) return false;
	if (!getFloat(pFondo, "velocidadDesplazamientoY", velocidadY)) return false;
	return true;
}

bool ServidorParser::getEscenario(Servidor* servidor, XMLNode* pNodoConfiguracion){
	// Nodo Escenario
	XMLElement * pNodoEscenario = pNodoConfiguracion -> FirstChildElement("escenario");

	// Longitud
	int longitud;
	if (!getInt(pNodoEscenario, "longitud", longitud)) return false;

	// Ventana
	int ancho, alto;
	if (!getVentana(pNodoEscenario, ancho, alto)) return false;

	// Fondo
	string pathSpriteFondo; int anchoFondo, altoFondo; float velocidadY;
	if (!getFondo(pNodoEscenario, pathSpriteFondo, anchoFondo, altoFondo, velocidadY)) return false;

	// NOTE el ancho y el alto del fondo ni los usamos?

	// Se crea el escenario y se lo setea al servidor
	EscenarioJuego* escenario = new EscenarioJuego(velocidadY, ancho, alto, longitud, pathSpriteFondo);
	servidor->setEscenario(escenario);

	// Elementos
	if (!agregarElementos(servidor, pNodoEscenario)) return false;

	return true;
}

bool ServidorParser::getElemento(XMLElement * pNodoElemento, string & pathSprite, float & posx, float & posy){
	if (!getString(pNodoElemento, "spriteIdElemento", pathSprite)) pathSprite = "";
	if (!getFloat(pNodoElemento, "posx", posx)) return false;
	if (!getFloat(pNodoElemento, "posx", posy)) return false;
	return true;
}

bool ServidorParser::agregarElementos(Servidor* servidor, XMLElement* pNodoEscenario){
	int alto = servidor->getEscenario()->getAlto();
	string spriteIdElemento;
	float posx, posy;

	// Nodo elementos
	XMLElement * pNodoElementos = pNodoEscenario -> FirstChildElement("elementos");
	if (!pNodoElementos) return false;

	// Iteramos sobre la lista de elementos
	XMLElement * pNodoElemento = pNodoElementos -> FirstChildElement("elemento");

	while( pNodoElemento != NULL ){

		if (getElemento(pNodoElemento, spriteIdElemento, posx, posy)) {
			servidor->getEscenario()->agregarElemento(posx, alto - posy, spriteIdElemento);
		}

		pNodoElemento = pNodoElemento -> NextSiblingElement("elemento");
	}

	return true;
}

bool ServidorParser::agregarAviones(Servidor* servidor, XMLNode * pNodoConfiguracion){
	float velocidadDesplazamiento, velocidadDisparos;
	string avionSpriteId, disparosSpriteId;

	XMLElement* pNodoAviones = pNodoConfiguracion->FirstChildElement("aviones");
	if (!pNodoAviones) return false;

	// Por ahora se asume que hay un solo modelo de avión. No se itera sobre una lista.
	XMLElement* pNodoAvion = pNodoAviones->FirstChildElement("avion");

	if (!getFloat(pNodoAvion, "velocidadDesplazamiento", velocidadDesplazamiento)) return false;
	if (!getFloat(pNodoAvion, "velocidadDisparos", velocidadDisparos)) return false;
	if (!getString(pNodoAvion, "avionSpriteId", avionSpriteId)) avionSpriteId = "";
	if (!getString(pNodoAvion, "disparosSpriteId", disparosSpriteId)) avionSpriteId = "";
	int ancho = servidor->getEscenario()->getAncho();
	int cantidadDeClientes = servidor->getCantidadMaximaDeClientes();
	float d = ancho/(cantidadDeClientes + 1);

	// Agregamos el mismo avión para todos los jugadores.
	for (int i = 1; i <= cantidadDeClientes; i++){
		servidor->getEscenario()->agregarAvion(d*i - ANCHO_AVION_COMUN/2, 600,
			velocidadDesplazamiento, velocidadDisparos, avionSpriteId, disparosSpriteId);
	}
	return true;
}

Servidor * ServidorParser::deserializarEscenario(string ruta){
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta.c_str());
	if (!archivoValido(eResult, ruta)) return NULL;

	XMLNode * pNodoConfiguracion = doc.FirstChildElement();
	//Nodo Servidor
	int unaCantidadDeClientes;
	int unPuerto;
	if(!getServidor(unaCantidadDeClientes, unPuerto, pNodoConfiguracion)){
		cout <<"Error en los elementos del archivo " + ruta  << endl;
		Logger::instance()->logWarning("Incoveniente en el nodo 'servidor' del archivo " + ruta);
		return NULL;
	}

	Servidor* servidor = new Servidor(unPuerto, unaCantidadDeClientes);

	if(!getEscenario(servidor, pNodoConfiguracion)){
		cout <<"Error en los elementos del archivo " + ruta  << endl;
		Logger::instance()->logWarning("Incoveniente en el nodo 'escenario' del archivo " + ruta);
		return NULL;
	}

	if(!agregarAviones(servidor, pNodoConfiguracion)){
		cout <<"Error en los elementos del archivo " + ruta  << endl;
		Logger::instance()->logWarning("Incoveniente en el nodo 'aviones' del archivo " + ruta);
		return NULL;
	}
	return servidor;

}
