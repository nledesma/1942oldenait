#include <iostream>
using namespace std;
#include "clienteParser.hpp"
#include "cliente.hpp"
#include "mensaje.hpp"
#include "tinyxml2.h"
#include "mensajeString.hpp"
#include "mensajeInt.hpp"
#include "mensajeChar.hpp"

int main(){

  //RAII
  Cliente cliente("127.0.0.1", 8080);
  // TODO MATAR MENSAJES.
  cliente.agregarMensaje(new MensajeString(1,"HOLA"));
  cliente.agregarMensaje(new MensajeInt(27,"1"));
  cliente.agregarMensaje(new MensajeChar(3,"A"));

  ClienteParser clParser;
  clParser.serializador(&cliente, "clientePrueba.xml");

  // Prueba del deserializador.
  Cliente cliente2 = clParser.deserializador("clientePrueba.xml");

  return 0;
}
