#include <iostream>
using namespace std;
#include "cliente/clienteParser.hpp"
#include "cliente.hpp"
#include "mensaje.hpp"
#include "tinyxml2.h"
#include "mensajeString.hpp"
#include "mensajeInt.hpp"
#include "mensajeChar.hpp"

int main(){
  Cliente cliente("127.0.0.1", 8080);
  MensajeString m1(1,"hola");
  MensajeInt m2(27,"1");
  MensajeChar m3(3,"A");

  cliente.agregarMensaje(&m1);
  cliente.agregarMensaje(&m2);
  cliente.agregarMensaje(&m3);

  ClienteParser clParser;
  clParser.serializador(&cliente, "clientePrueba.xml");

  // Prueba del deserializador.
  Cliente cliente2 = clParser.deserializador("clientePrueba.xml");

  return 0;
}
