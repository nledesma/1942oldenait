#include "servidorParser.hpp"
#include "../../juego/modelo/escenarioJuego.hpp"
#include "../../juego/modelo/disparo.hpp"
#include "../../juego/modelo/avion.hpp"
#include "../../juego/modelo/elemento.hpp"


#define DEFAULT_XML_NIVEL "../../../resources/xml/niveles/nivel1.xml"

using namespace std;
using namespace tinyxml2;

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

Servidor * ServidorParser::deserializar(string ruta) {
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta.c_str());
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
		return NULL;
	}


	XMLNode * pRoot = doc.FirstChildElement();
	XMLNode * pNodoCantidadMaximaDeClientes = pRoot -> FirstChild();
	int cantidadMaximaDeClientes;
	if((pNodoCantidadMaximaDeClientes == 0) || (string(pNodoCantidadMaximaDeClientes -> Value()) != "cantidadMaximaDeClientes") || (!laCantidadEsValida(pNodoCantidadMaximaDeClientes, cantidadMaximaDeClientes))) {
		cout <<"Error en los elementos del archivo " + ruta  << endl;
		Logger::instance()->logWarning("Incoveniente en la cantidad de clientes del archivo " + ruta);
		Logger::instance()->logInfo("Se procede a cargar el archivo por defecto");
		return NULL;
	}

	XMLNode * pNodoPuerto =  pNodoCantidadMaximaDeClientes -> NextSibling();

	int unPuerto;

	if((pNodoPuerto == 0) || (string(pNodoPuerto -> Value()) != "puerto") || (!elPuertoEsValido(pNodoPuerto, unPuerto))) {
		cout <<"Error en los elementos del archivo " + ruta  << endl;
		Logger::instance()->logWarning("Incoveniente en el puerto del archivo " + ruta);
		Logger::instance()->logInfo("Se procede a cargar el archivo por defecto");
		return NULL;
	}
	Servidor* servidor = new Servidor(unPuerto, cantidadMaximaDeClientes);
	return servidor;
}

bool ServidorParser::elPuertoEsValido(XMLNode * pNodoPuerto, int &unPuerto) {
	if (!(pNodoPuerto->ToElement()->GetText() == nullptr)) {
			pNodoPuerto ->ToElement() -> QueryIntText(&unPuerto);
			return((unPuerto>=1024)&&(unPuerto<65535));
	} else {
		return false;
	}
}

bool ServidorParser::laCantidadEsValida(XMLNode * pNodoCantidadClientes, int &cantidadDeClientes) {
	if(!(pNodoCantidadClientes -> ToElement() -> GetText() == nullptr)) {
		pNodoCantidadClientes -> ToElement() -> QueryIntText(&cantidadDeClientes);
		return(cantidadDeClientes > 0);
	} else {
		return false;
	}
}

Servidor * ServidorParser::deserializarEscenario(string ruta) {
	XMLDocument doc;
	XMLError eResult = doc.LoadFile(ruta.c_str());
	XMLNode * pRoot = doc.FirstChildElement();
	//Nodo Servidor
	XMLNode * pNodoServidor = pRoot -> FirstChild();
	int unaCantidadDeClientes;
	XMLNode * pNodoCantidadMaximaDeClientes = pNodoServidor -> FirstChild();
	pNodoCantidadMaximaDeClientes -> ToElement() -> QueryIntText(&unaCantidadDeClientes);

	int unPuerto;
	XMLNode * pNodoPuerto =  pNodoCantidadMaximaDeClientes -> NextSibling();
	pNodoPuerto -> ToElement() -> QueryIntText(&unPuerto);

	//Nodo Escenario
	XMLNode * pNodoEscenario = pRoot -> FirstChild()-> NextSibling();
	//Nodo Ventana
	XMLNode * pNodoVentana = pNodoEscenario -> FirstChild();
	//Ancho
	int ancho;
	XMLNode* pNodoAncho = pNodoVentana->FirstChild();
	pNodoAncho -> ToElement() -> QueryIntText(&ancho);

	//Alto
	int alto;
	XMLNode* pNodoAlto = pNodoVentana->FirstChild()->NextSibling();
	pNodoAlto -> ToElement() -> QueryIntText(&alto);

	//Nodo Fondo
	XMLNode* pNodoFondo = pNodoEscenario->FirstChild()->NextSibling();

	//Id fondo sprite
	const char* idSprite;
	XMLNode* pIdSpriteFondo = pNodoFondo->FirstChild();
	idSprite = pIdSpriteFondo->ToElement()->GetText();

	//Ancho del fondo
	int anchoFondo;
	XMLNode* pNodoAnchoFondo = pNodoFondo->FirstChild()->NextSibling();
	pNodoAnchoFondo -> ToElement() -> QueryIntText(&anchoFondo);

	//Alto del fondo
	int altoFondo;
	XMLNode* pNodoAltoFondo = pNodoFondo->FirstChild()->NextSibling()->NextSibling();
	pNodoAltoFondo -> ToElement() -> QueryIntText(&altoFondo);

	//Velocidad de desplazamiento del fondo
	float velocidadDesplazamientoY;
	XMLNode* pdNodoVelocidadDesplazamientoYFondo = pNodoFondo->FirstChild()->NextSibling()->NextSibling()->NextSibling();
	pdNodoVelocidadDesplazamientoYFondo ->ToElement() ->QueryFloatText(&velocidadDesplazamientoY);

	//Nodo elementos
	XMLNode* pNodoElementos = pNodoEscenario->FirstChild()->NextSibling()->NextSibling();

	Servidor* servidor = new Servidor(unPuerto,unaCantidadDeClientes);
	EscenarioJuego* escenario = new EscenarioJuego(ancho,alto, velocidadDesplazamientoY);
	servidor->setEscenario(escenario);
	cout << "Se creo un escenario" << endl;

	//Lista de elementos
	XMLNode * pNodoElemento = pNodoElementos -> FirstChild();

	while(pNodoElemento != NULL){
		string spriteIdElemento;
		float posx, posy;
		XMLNode* pNodoSpriteIdElemento = pNodoElemento->FirstChild();
		spriteIdElemento = pNodoSpriteIdElemento -> ToElement() -> GetText();
		XMLNode* pNodoPosX = pNodoElemento->FirstChild()->NextSibling();
		pNodoPosX->ToElement()->QueryFloatText(&posx);
		XMLNode* pNodoPosY = pNodoElemento->FirstChild()->NextSibling()->NextSibling();
		pNodoPosY->ToElement()->QueryFloatText(&posy);
		servidor->getEscenario()->agregarElemento(spriteIdElemento, posx, alto - posy);

		pNodoElemento = pNodoElemento -> NextSiblingElement("elemento");
	}

	//Lista de aviones
	XMLNode* pNodoAviones = pRoot -> FirstChild()-> NextSibling()->NextSibling();
	XMLNode* pNodoAvion = pNodoAviones->FirstChild();
	while(pNodoAvion != NULL){
		float velocidadDesplazamiento, velocidadDisparos;
		string avionSpriteId, vueltaSpriteId, disparosSpriteId;
		//Velocidad de desplazamiento
		XMLNode* pVelocidadDesplazamiento = pNodoAvion->FirstChild();
		pVelocidadDesplazamiento->ToElement()->QueryFloatText(&velocidadDesplazamiento);
		//Velocidad Disparos
		XMLNode* pVelocidadDisparos = pNodoAvion->FirstChild()->NextSibling();
		pVelocidadDisparos->ToElement()->QueryFloatText(&velocidadDisparos);
		//Avion ID Sprite
		XMLNode* pNodoSpriteIdAvion = pVelocidadDisparos->NextSibling();
		avionSpriteId = pNodoSpriteIdAvion -> ToElement() -> GetText();
		//Avion ID Sprite Vuelta
		XMLNode* pNodoSpriteIdAvionVuelta = pNodoSpriteIdAvion->NextSibling();
		vueltaSpriteId = pNodoSpriteIdAvionVuelta -> ToElement() -> GetText();
		//Avion ID Sprite Disparos
		XMLNode* pNodoSpriteIdAvionDisparos = pNodoSpriteIdAvionVuelta->NextSibling();
		disparosSpriteId = pNodoSpriteIdAvionDisparos -> ToElement() -> GetText();

		servidor->getEscenario()->agregarAvion(velocidadDesplazamiento, velocidadDisparos, avionSpriteId, vueltaSpriteId, disparosSpriteId);

		pNodoAvion = pNodoAvion -> NextSiblingElement("avion");
	}


	return servidor;
}
