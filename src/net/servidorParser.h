#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring> // Necesario para el memset.
#include <cstdio>
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "servidor.cpp"
#include <list>
#include <iterator>

using namespace std;
using namespace tinyxml2;

public class ServidorParser{
public:
	Servidor * deserializar(string ruta);
	void serializar(Servidor *servidor, string ruta);
}