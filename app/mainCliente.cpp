#include "../src/net/cliente/cliente.hpp"
#include "../src/net/cliente/clienteParser.hpp"
#include "../src/net/gameSocket.hpp"
#include <list>
#include <iostream>     // std::cout
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <sys/time.h>

using namespace std;

// void miFuncion(Mensaje * mensaje) {
//   cout << mensaje -> getId() << endl;
// }
//
int main() {

  ClienteParser * clienteParser = new ClienteParser();
	string url = "../resources/xml/clienteDefault.xml";
  Cliente * cliente = clienteParser->deserializador(url);
  // cliente->inicializar("h", 8080 );
 // 	cliente->enviarMensajePorId(2);
 cliente->ciclarMensajes(3000);

	return 0;
}
