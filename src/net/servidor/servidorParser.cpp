#include "servidorParser.hpp"
#include "../../juego/modelo/trayectoriasEnemigos/fabricaEnemigos.hpp"

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

	if (nClientes < 1 || nClientes > 6) {
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

bool ServidorParser::getEtapa(XMLElement * pEtapa, Etapa * & etapa, EscenarioJuego* escenarioJuego) {
	int longitud;
	int altoVentana = escenarioJuego->getAltoVentana();
	int anchoFondo = escenarioJuego->getAncho();
	int altoFondo = escenarioJuego->getAlto();

	if (!getInt(pEtapa, "longitud", longitud)) return false;
	etapa = new Etapa(longitud);
	int longitudEtapa = etapa->getLongitud();
	// Agregar Elementos.
	if (!agregarElementos(etapa, pEtapa, altoVentana)) return false;
	// Agregar Enemigos
	if(!agregarEnemigos(etapa,pEtapa, anchoFondo, altoFondo, longitudEtapa)) return false;
	//Agregar PowerUps
	if(!agregarPowerUps(etapa,pEtapa,anchoFondo,altoFondo,longitudEtapa)) return false;
	return true;
}

bool ServidorParser::agregarEtapas(EscenarioJuego *escenario, XMLElement *pEscenario) {
	XMLElement * pEtapas = pEscenario->FirstChildElement("etapas");
	if (!pEtapas) return false;

	XMLElement * pEtapa = pEtapas->FirstChildElement("etapa");
	while (pEtapa != NULL) {
		Etapa * etapa;
		if (getEtapa(pEtapa, etapa, escenario)) escenario->agregarEtapa(etapa);
		pEtapa = pEtapa->NextSiblingElement("etapa");
	}

	return true;
}

bool ServidorParser::getModo(XMLElement * pNodoEscenario, int & modo) {
	string modoStr;
	if (!getString(pNodoEscenario, "modo", modoStr)) {
		Logger::instance()->logWarning("No se encontró modo de juego en el XML");
		return false;
	}

	// NOTE por ahí podría ser un bool que se llame modoEquipos.
	if (modoStr == "equipos") {
		modo = EQUIPOS;
		return true;
	}

	if (modoStr == "colaborativo") {
		modo = COLABORATIVO;
		return true;
	}

	Logger::instance()->logWarning("El modo de juego del XML no es correcto.");
	return false;
}

bool ServidorParser::getEscenario(Servidor* servidor, XMLNode* pNodoConfiguracion){
	// Nodo Escenario
	XMLElement * pNodoEscenario = pNodoConfiguracion -> FirstChildElement("escenario");

	// Ventana
	int anchoVentana, altoVentana;
	if (!getVentana(pNodoEscenario, anchoVentana, altoVentana)) return false;

	// Fondo.
	string pathSpriteFondo; int anchoFondo, altoFondo; float velocidadY;
	if (!getFondo(pNodoEscenario, pathSpriteFondo, anchoFondo, altoFondo, velocidadY)) return false;

	// Modo.
	int modo;
	if (!getModo(pNodoEscenario, modo)) return false;

	// Se crea el escenario y se lo setea al servidor.
	EscenarioJuego* escenario = new EscenarioJuego(velocidadY, anchoFondo, altoFondo, anchoVentana, altoVentana, pathSpriteFondo, modo);

	// Se agregan las etapas.
	if (!agregarEtapas(escenario, pNodoEscenario)) return false;
	servidor->setEscenario(escenario);

	return true;
}

bool ServidorParser::getElemento(XMLElement * pNodoElemento, string & pathSprite, float & posx, float & posy){
	if (!getString(pNodoElemento, "spriteIdElemento", pathSprite)) pathSprite = "";
	if (!getFloat(pNodoElemento, "posx", posx)) return false;
	if (!getFloat(pNodoElemento, "posy", posy)) return false;
	return true;
}

bool ServidorParser::getEnemigo(XMLElement * pNodoElemento, string &tipo, int &cantidad){
	if (!getString(pNodoElemento, "tipo", tipo)) tipo = "";
	if (!getInt(pNodoElemento, "cantidad", cantidad)) return false;
	return true;
}

bool ServidorParser::getPowerUp(XMLElement * pNodoElemento, string &tipo, float &posx, float &posy, int &valor){
	if (!getString(pNodoElemento, "tipo", tipo)) tipo = "";
	if (!getFloat(pNodoElemento, "posx", posx)) posx = 0;
	if (!getFloat(pNodoElemento, "posy", posy)) posy = 0;
	if (!getInt(pNodoElemento, "valor", valor)) return false;
	return true;
}

bool ServidorParser::agregarPowerUps(Etapa * etapa, XMLElement* pNodoEtapa, int anchoFondo, int altoFondo, int longitudEtapa){

	string tipo;
	float posx = 0, posy = 0;
	int valor = 0;
	list <PowerUpParseado*> powerUpsParseados;
	// Nodo power ups
	XMLElement * pNodoPowerUps = pNodoEtapa -> FirstChildElement()->NextSiblingElement("powerUps");
	if (!pNodoPowerUps) return false;

	// Iteramos sobre la lista de powerUps
	XMLElement * pNodoPowerUp = pNodoPowerUps -> FirstChildElement("powerUp");

	while( pNodoPowerUp != NULL ){
		PowerUpParseado* unPowerUpParseado = new PowerUpParseado();
		if (getPowerUp(pNodoPowerUp, tipo, posx, posy, valor)) {
			unPowerUpParseado->setTipo(tipo);
			unPowerUpParseado->setPosX(posx);
			unPowerUpParseado->setPosY(posy);
			unPowerUpParseado->setValor(valor);
			powerUpsParseados.push_back(unPowerUpParseado);
		}
		pNodoPowerUp = pNodoPowerUp -> NextSiblingElement("powerUp");
	}

	FabricaPowerUps* fabricaPowerUps = new FabricaPowerUps();
	list <PowerUp*> listaPowerUps = fabricaPowerUps->fabricarPowerUps(powerUpsParseados,longitudEtapa,anchoFondo,altoFondo);

	//TODO: Descomentar esto cuando tenga la lista de PowerUps
	etapa->setPowerUps(listaPowerUps);
	return true;
}

bool ServidorParser::agregarEnemigos(Etapa * etapa, XMLElement* pNodoEtapa, int anchoFondo, int altoFondo,
									 int longitudEtapa){
	string tipo;
	int cantidad = 0;
	int cantidadPequenios = 0;
	int cantidadEscuadrones = 0;
	int cantidadMedianos = 0;
	int cantidadGrandes = 0;
	// Nodo enemigos
	XMLElement * pNodoEnemigos = pNodoEtapa -> FirstChildElement()->NextSiblingElement("enemigos");
	if (!pNodoEnemigos) return false;

	// Iteramos sobre la lista de enemigos
	XMLElement * pNodoEnemigo = pNodoEnemigos -> FirstChildElement("enemigo");

	//FabricaEnemigos * fabrica = new FabricaEnemigos();
	while( pNodoEnemigo != NULL ){

		if (getEnemigo(pNodoEnemigo, tipo, cantidad)) {
			if (tipo == "pequenio"){
				cantidadPequenios = cantidad;
			} else if (tipo == "mediano"){
				cantidadMedianos = cantidad;
			} else if (tipo == "escuadron"){
				cantidadEscuadrones = cantidad;
			} else if (tipo == "grande"){
				cantidadGrandes = cantidad;
			}
			cout << "Se agregaran " << cantidad << " aviones del tipo " << tipo << endl;
		}

		pNodoEnemigo = pNodoEnemigo -> NextSiblingElement("enemigo");
	}

	FabricaEnemigos* fabricaEnemigos = new FabricaEnemigos();
	list< pair<float, AvionEnemigo*> > listaEnemigos = fabricaEnemigos->fabricarEnemigos(cantidadPequenios,
																						 cantidadEscuadrones,
																						 cantidadMedianos,
																						 cantidadGrandes, longitudEtapa,
																						 anchoFondo, altoFondo);
	etapa->setEnemigos(listaEnemigos);
	return true;
}

bool ServidorParser::agregarElementos(Etapa * etapa, XMLElement* pNodoEtapa, int altoVentana){
	string spriteIdElemento;
	float posx, posy;

	etapa->agregarElemento(50, altoVentana - etapa->getLongitud(), SPRITE_MOTHERSHIP);

	// Nodo elementos
	XMLElement * pNodoElementos = pNodoEtapa -> FirstChildElement("elementos");
	if (!pNodoElementos) return false;

	// Iteramos sobre la lista de elementos
	XMLElement * pNodoElemento = pNodoElementos -> FirstChildElement("elemento");

	while( pNodoElemento != NULL ){

		if (getElemento(pNodoElemento, spriteIdElemento, posx, posy)) {
			etapa->agregarElemento(posx, altoVentana - posy, spriteIdElemento);
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
	int cantidadDeClientes = servidor->getCantidadMaximaDeClientes();

	// Agregamos el mismo avión para todos los jugadores.
	for (int i = 1; i <= cantidadDeClientes; i++){
		servidor->getEscenario()->agregarAvion(velocidadDesplazamiento,
			velocidadDisparos + velocidadDesplazamiento,
			avionSpriteId, disparosSpriteId);
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
