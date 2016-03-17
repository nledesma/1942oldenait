#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
#include "tinyxml2.cpp"
#include "cliente.cpp"
#include <list>

using namespace std;
using namespace tinyxml2;

class ClienteParser {
	//El cliente recibe una direccion IP, un puerto y una coleccion de mensajes de tamaño indefinido
	public: void serializador(Cliente cliente,string ruta);
	public: Cliente deserializador(string ruta);
};

void ClienteParser::serializador(Cliente cliente, string ruta){
    XMLDocument doc;

    // Root
    XMLNode * pRoot = doc.NewElement("Cliente");
    doc.InsertFirstChild(pRoot);

    // Hijos del root. TODO: diferencia entre element y node.
    XMLElement * pNodoIp = doc.NewElement("ip");
    (*pNodoIp).SetText(10);

	XMLElement * pNodoPort = doc.NewElement("port");
    // castear a string?
    (*pNodoPort).SetText(10);

	XMLElement * pNodoMensajes = doc.NewElement("mensajes");
    // castear a string?

	for (int i = 0 ; i < cliente->getMensajes().size(); i++){
		XMLElement * pListaMensajes = xmlDoc.NewElement("mensaje");
		pListaMensajes-> SetText(mensaje);

		XMLElement * pListaMensajes = xmlDoc.NewElement("id");
		pListaMensajes-> SetText(id);

		XMLElement * pListaMensajes = xmlDoc.NewElement("tipo");
		pListaMensajes-> SetText(tipo);

		XMLElement * pListaMensajes = xmlDoc.NewElement("valor");
		pListaMensajes-> SetText(valor);

		pMensaje->InsertEndChild(pListaMensajes);
		}
	}

    (*pNodoMensajes).SetText(10);

    // Inserto ambos elementos al root.
    pRoot -> InsertFirstChild(pNodoIp);
    pRoot -> InsertFirstChild(pNodoPort);
    pRoot -> InsertFirstChild(pNodoMensajes);

    XMLError e = doc.SaveFile("cliente.xml");
    if (e != XML_SUCCESS){
	    cout << "Error! " << e << endl;
    }
}