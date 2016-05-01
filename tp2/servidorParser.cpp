#include "servidorParser.hpp"

using namespace std;
using namespace tinyxml2;

void ServidorParser::serializar(Servidor * servidor, string ruta) {
	XMLDocument doc;
	//Configuracion
	XMLNode * pConfiguracion = doc.NewElement("configuracion");
	doc.InsertEndChild(pConfiguracion);
	//Servidor
	XMLElement *pServidor = doc.NewElement("servidor");
	doc.InsertEndChild(pServidor);

	XMLElement * pNodoCantidadMaximaDeClientes = doc.NewElement("cantidadMaximaDeClientes");
	(*pNodoCantidadMaximaDeClientes).SetText(servidor -> getCantidadMaximaDeClientes());

	XMLElement * pNodoPuerto = doc.NewElement("puerto");
	(*pNodoPuerto).SetText(servidor -> getPuerto());

	pServidor->InsertEndChild(pNodoCantidadMaximaDeClientes);
	pServidor->InsertEndChild(pNodoPuerto);

	//Escenario
  XMLElement * pNodoEscenario = doc.NewElement("escenario");
	pConfiguracion -> InsertEndChild(pNodoEscenario);
	//Ventana
  XMLElement* pNodoVentana = doc.NewElement("ventana");

	XMLElement * pNodoAncho = doc.NewElement("ancho");
	pNodoAncho-> SetText(servidor -> getEscenario()->getVentana()->getAncho());
	pNodoVentana->InsertEndChild(pNodoAncho);

	XMLElement * pNodoAlto = doc.NewElement("alto");
	pNodoAlto-> SetText(servidor -> getEscenario()->getVentana()->getAlto());
	pNodoVentana->InsertEndChild(pNodoAlto);

	XMLElement* pNodoFondo = doc.NewElement("fondo");
	pNodoEscenario->InsertEndChild(pNodoFondo);

	XMLElement* pNodoIdSpriteFondo = doc.NewElement("spriteIdFondo");
	pNodoIdSpriteFondo->SetText(servidor->getEscenario()->getFondoSprite());
	pNodoFondo->InsertEndChild(pNodoIdSpriteFondo);

	XMLElement* pNodoAnchoFondo = doc.NewElement("ancho");
	pNodoAnchoFondo->SetText(servidor->getEscenario()->getAnchoFondo());
	pNodoFondo->InsertEndChild(pNodoAnchoFondo);

	XMLElement* pNodoAltoFondo = doc.NewElement("alto");
	pNodoAltoFondo->SetText(servidor->getEscenario()->getAltoFondo());
	pNodoFondo->InsertEndChild(pNodoAltoFondo);

	XMLElement* pNodoElementos = doc.NewElement("elementos");
	pNodoEscenario->InsertEndChild(pNodoElementos);

	for(list<Elemento*>::iterator iterador = servidor->getEscenario()->getElementos().begin(); iterador != servidor->getEscenario()->getElementos().end(); ++iterador){
		XMLElement * pElemento = doc.NewElement("elemento");
		Elemento *elemento = *iterador;

		// ID Sprite Elemento
		XMLElement * pIdSpriteElemento = doc.NewElement("spriteIdElemento");
		pIdSpriteElemento -> SetText(elemento->getSpriteId().c_str());
		pElemento ->InsertEndChild(pIdSpriteElemento);

		// Posicion X del elemento
		XMLElement * pPosX = doc.NewElement("posx");
		pPosX-> SetText(elemento->getPosX());
		pElemento->InsertEndChild(pPosX);

		// Posicion Y del elemento
		XMLElement * pPosY = doc.NewElement("posy");
		pPosY-> SetText(elemento->getPosY());
		pElemento->InsertEndChild(pPosY);

		// Agrego el elemento a la lista de elementos
		pNodoElementos->InsertEndChild(pElemento);
	}

	XMLError e = doc.SaveFile(ruta.c_str());
	if (e != XML_SUCCESS) {
		cout << "Error creando en la ubicación " + ruta << e << endl;
	}
}

Servidor * ServidorParser::deserializar(string ruta) {
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

	//Nodo elementos
	XMLNode* pNodoElementos = pNodoEscenario->FirstChild()->NextSibling()->NextSibling();

	Servidor* servidor = new Servidor(unPuerto,unaCantidadDeClientes);
	Escenario* escenario = new Escenario(ancho,alto);
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
		servidor->getEscenario()->agregarElemento(spriteIdElemento, posx, posy);

		pNodoElemento = pNodoElemento -> NextSiblingElement("elemento");
}

	return servidor;
}
