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
	if(!getInt(pNodoServidor,"puerto", puerto)) return false;
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

bool ServidorParser::validarContenidoTagInt(XMLNode* pNodoInt, int &unInt){
	if(!(pNodoInt->ToElement()->GetText() == nullptr)){
		pNodoInt -> ToElement() -> QueryIntText(&unInt);
			return (unInt > 0);
	}else {
		return false;
	}
}

bool ServidorParser::validarContenidoTagString(XMLNode* pNodoStr, string &unStr){
	if(!((pNodoStr == NULL) || (pNodoStr->ToElement()->GetText() == nullptr))){
		unStr = pNodoStr->ToElement()->GetText();
		return true;
	}
	return false;
}

bool ServidorParser::validarContenidoTagFloat(XMLNode* pNodoFloat, float &unFloat){
	if(!(pNodoFloat->ToElement()->GetText() == nullptr)){
		pNodoFloat -> ToElement() -> QueryFloatText(&unFloat);
		return (unFloat > 0);
	}else {
		return false;
	}
}

bool ServidorParser::getServidor(int & cantidadClientes, int &puerto, XMLNode *pRoot){
	XMLElement * pNodoServidor = pRoot -> FirstChildElement("servidor");

	//Cantidad Maxima de Clientes
	if (!getCantidadClientes(pNodoServidor, cantidadClientes)) return false;

	//Puerto
	if (!getPuerto(pNodoServidor, puerto)) return false;

	return true;
}

bool ServidorParser::nodoEscenarioValido(Servidor* servidor, XMLNode* pNodoConfiguracion){
	//Nodo Escenario
	XMLNode * pNodoEscenario = pNodoConfiguracion -> FirstChild()-> NextSibling();
	//Nodo Longitud
	int longitud;
	XMLNode * pNodoLongitud = pNodoEscenario -> FirstChild();
	if(!validarContenidoTagInt(pNodoLongitud, longitud)) return false;
	//Nodo Ventana
	XMLNode * pNodoVentana = pNodoLongitud->NextSibling();
	//Ancho
	int ancho;
	XMLNode* pNodoAncho = pNodoVentana->FirstChild();
	if(!validarContenidoTagInt(pNodoAncho, ancho)) return false;
	//Alto
	int alto;
	XMLNode* pNodoAlto = pNodoVentana->FirstChild()->NextSibling();
	if(!validarContenidoTagInt(pNodoAlto, alto)) return false;
	//Nodo Fondo
	XMLNode* pNodoFondo = pNodoVentana->NextSibling();
	//Id fondo sprite
	string idSprite;
	XMLNode* pIdSpriteFondo = pNodoFondo->FirstChild();
	if(!validarContenidoTagString(pIdSpriteFondo, idSprite)) return false;
	//Ancho del fondo
	int anchoFondo;
	XMLNode* pNodoAnchoFondo = pNodoFondo->FirstChild()->NextSibling();
	if(!validarContenidoTagInt(pNodoAnchoFondo, anchoFondo)) return false;
	//Alto del fondo
	int altoFondo;
	XMLNode* pNodoAltoFondo = pNodoFondo->FirstChild()->NextSibling()->NextSibling();
	if(!validarContenidoTagInt(pNodoAltoFondo, altoFondo)) return false;
	//Velocidad de desplazamiento del fondo
	float velocidadDesplazamientoY;
	XMLNode* pdNodoVelocidadDesplazamientoYFondo = pNodoFondo->FirstChild()->NextSibling()->NextSibling()->NextSibling();
	if(!validarContenidoTagFloat(pdNodoVelocidadDesplazamientoYFondo, velocidadDesplazamientoY)) return false;
	// Se crea el escenario y se lo setea al servidor
	EscenarioJuego* escenario = new EscenarioJuego(velocidadDesplazamientoY, ancho, alto, longitud, idSprite);
	servidor->setEscenario(escenario);
	nodoElementosValido(servidor, pNodoEscenario);
	return true;
}

bool ServidorParser::nodoElementosValido(Servidor* servidor, XMLNode* pNodoEscenario){
	//Nodo elementos
	XMLNode* pNodoElementos = pNodoEscenario -> FirstChild()->NextSibling()->NextSibling()->NextSibling();
	//Lista de elementos
	XMLNode * pNodoElemento = pNodoElementos -> FirstChild();
	//TODO quizás habria que validar los elementos dentro del while. Revisar!
	while(pNodoElemento != NULL){
		string spriteIdElemento;
		float posx, posy;
		XMLNode* pNodoSpriteIdElemento = pNodoElemento->FirstChild();
		spriteIdElemento = pNodoSpriteIdElemento->ToElement()->GetText();
		XMLNode* pNodoPosX = pNodoElemento->FirstChild()->NextSibling();
		pNodoPosX->ToElement()->QueryFloatText(&posx);
		XMLNode* pNodoPosY = pNodoElemento->FirstChild()->NextSibling()->NextSibling();
		pNodoPosY->ToElement()->QueryFloatText(&posy);
		int alto = servidor->getEscenario()->getAlto();
		servidor->getEscenario()->agregarElemento(posx, alto - posy, spriteIdElemento);

		pNodoElemento = pNodoElemento -> NextSiblingElement("elemento");
	}
	return true;
}

bool ServidorParser::nodoAvionesValido(Servidor* servidor, XMLNode * pNodoConfiguracion){

	XMLNode* pNodoAviones = pNodoConfiguracion -> FirstChild()-> NextSibling()->NextSibling();
	XMLNode* pNodoAvion = pNodoAviones->FirstChild();
	float velocidadDesplazamiento, velocidadDisparos;
	string avionSpriteId, vueltaSpriteId, disparosSpriteId;
	//Velocidad de desplazamiento
	XMLNode* pVelocidadDesplazamiento = pNodoAvion->FirstChild();
	if(!validarContenidoTagFloat(pVelocidadDesplazamiento, velocidadDesplazamiento)) return false;
	//Velocidad Disparos
	XMLNode* pVelocidadDisparos = pNodoAvion->FirstChild()->NextSibling();
	if(!validarContenidoTagFloat(pVelocidadDisparos, velocidadDisparos)) return false;
	//Avion ID Sprite
	XMLNode* pNodoSpriteIdAvion = pVelocidadDisparos->NextSibling();
	if(!validarContenidoTagString(pNodoSpriteIdAvion, avionSpriteId)) return false;
	//Avion ID Sprite Disparos
	XMLNode* pNodoSpriteIdAvionDisparos = pNodoSpriteIdAvion->NextSibling();
	if(!validarContenidoTagString(pNodoSpriteIdAvionDisparos, disparosSpriteId)) return false;

	int ancho = servidor->getEscenario()->getAncho();
	int unaCantidadDeClientes = servidor->getCantidadMaximaDeClientes();
	float d = ancho/(unaCantidadDeClientes + 1);
	for (int i = 1; i <= unaCantidadDeClientes; i++){
		servidor->getEscenario()->agregarAvion(d*i - ANCHO_AVION_COMUN/2, 600,
			velocidadDesplazamiento, velocidadDisparos, avionSpriteId, disparosSpriteId);
	}
	return true;
}

bool ServidorParser::archivoValido(XMLError eResult, string ruta){
	if (eResult != XML_NO_ERROR){
		if(eResult >= 16){
			cout << "El archivo" + ruta +"  no es válido" << endl;
			Logger::instance()->logWarning("Archivo " + ruta + " invalido.");
		}else if (eResult == XML_ERROR_PARSING_ELEMENT || eResult == XML_ERROR_ELEMENT_MISMATCH || eResult == XML_ERROR_IDENTIFYING_TAG) {
			cout << "El archivo " + ruta + " está malformado." << endl;
			Logger::instance()->logWarning("El archivo " + ruta + " está malformado.");
		} else if (eResult == XML_ERROR_FILE_COULD_NOT_BE_OPENED || eResult == XML_ERROR_FILE_READ_ERROR) {
			cout << "El archivo " + ruta + " está malformado." << endl;
			Logger::instance()->logWarning("El archivo " + ruta + " está malformado.");
		} else if (eResult == XML_ERROR_FILE_NOT_FOUND){
			cout << "Ruta " + ruta + " inválida." << endl;
			Logger::instance()->logWarning("Ruta " + ruta + " inválida.");
		}

		return false;
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
	if(!nodoEscenarioValido(servidor, pNodoConfiguracion)){
		cout <<"Error en los elementos del archivo " + ruta  << endl;
		Logger::instance()->logWarning("Incoveniente en el nodo 'escenario' del archivo " + ruta);
		return NULL;
	}
	if(!nodoAvionesValido(servidor, pNodoConfiguracion)){
		cout <<"Error en los elementos del archivo " + ruta  << endl;
		Logger::instance()->logWarning("Incoveniente en el nodo 'aviones' del archivo " + ruta);
		return NULL;
	}
	return servidor;

}
