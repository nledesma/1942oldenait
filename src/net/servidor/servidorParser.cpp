#include "servidorParser.hpp"
#include "../../juego/modelo/escenarioJuego.hpp"
#include "../../juego/modelo/disparo.hpp"
#include "../../juego/modelo/avion.hpp"
#include "../../juego/modelo/elemento.hpp"


//#define DEFAULT_XML_NIVEL "../../../resources/xml/niveles/nivel1.xml"

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
		if(cantidadDeClientes > 4) return false;
		return(cantidadDeClientes > 0);
	} else {
		return false;
	}
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

bool ServidorParser::nodoServidorValido(int &unaCantidadDeClientes, int &unPuerto, XMLNode *pRoot){
	XMLNode * pNodoServidor = pRoot -> FirstChild();
	//Cantidad Maxima de Clientes
	XMLNode * pNodoCantidadMaximaDeClientes = pNodoServidor -> FirstChild();
	if((pNodoCantidadMaximaDeClientes == 0) || (string(pNodoCantidadMaximaDeClientes -> Value()) != "cantidadMaximaDeClientes") || (!laCantidadEsValida(pNodoCantidadMaximaDeClientes, unaCantidadDeClientes))) {
		return false;
	}
	pNodoCantidadMaximaDeClientes -> ToElement() -> QueryIntText(&unaCantidadDeClientes);
	//Puerto
	XMLNode * pNodoPuerto =  pNodoCantidadMaximaDeClientes -> NextSibling();
	if((pNodoPuerto == 0) || (string(pNodoPuerto -> Value()) != "puerto") || (!elPuertoEsValido(pNodoPuerto, unPuerto))) {
		return false;
	}
	pNodoPuerto -> ToElement() -> QueryIntText(&unPuerto);

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
	if(!nodoServidorValido(unaCantidadDeClientes, unPuerto, pNodoConfiguracion)){
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
