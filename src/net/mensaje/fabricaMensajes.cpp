#include "fabricaMensajes.hpp"
#include <string>
#include <iostream>
using namespace std;

Mensaje *FabricaMensajes::fabricarMensaje(int id, string tipo, string valor){
  if (tipo == "string") return new MensajeString(id, valor);
  if (tipo == "int") return new MensajeInt(id, valor);
  if (tipo == "double") return new MensajeDouble(id, valor);
  if (tipo == "char") return new MensajeChar(id, valor);
  // TODO LOG.
  cout << "Tipo no válido, no se pudo crear mensaje." << endl;
  return NULL;
}
