#include <iostream>
using namespace std;
#include "clienteParser.hpp"
#include "cliente.hpp"
#include "mensaje.hpp"
#include "tinyxml2.h"
#define T_STRING 0
#define T_INT 1
#define T_DOUBLE 2
#define T_CHAR 3

int main(){
  //RAII
  Cliente cliente("127.0.0.1", 8080);
  // TODO MATAR MENSAJES.
  cliente.agregarMensaje(new Mensaje(1,"HOLA",T_STRING));
  cliente.agregarMensaje(new Mensaje(27,"1",T_INT));
  cliente.agregarMensaje(new Mensaje(3,"A",T_CHAR));

  ClienteParser clParser;
  clParser.serializador(&cliente, "clientePrueba.xml");
  return 0;
}
