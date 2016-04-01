#include "fabricaMensajes.hpp"

Mensaje *FabricaMensajes::fabricarMensaje(int id, string tipo, string valor){
  if (tipo == "string") return new MensajeString(id, valor);
  if (tipo == "int") return new MensajeInt(id, valor);
  if (tipo == "double") return new MensajeDouble(id, valor);
  if (tipo == "char") return new MensajeChar(id, valor);

  stringstream ss;
  ss << "Tipo no válido, no se puede crear mensaje. Tipo: " << tipo << endl;
  Logger::instance()->log(ss.str());
  cout << ss.str() << endl;

  return NULL;
}

Mensaje * FabricaMensajes::fabricarMensaje(infoMensaje datos, char *valor){
  if (datos.tipo == T_STRING) return new MensajeString(datos,valor);
  if (datos.tipo == T_INT) return new MensajeInt(datos,valor);
  if (datos.tipo == T_DOUBLE) return new MensajeDouble(datos,valor);
  if (datos.tipo == T_CHAR) return new MensajeChar(datos,valor);

  stringstream ss;
  ss << "Tipo no válido, no se puede crear mensaje. Tipo: " << datos.tipo << endl;
  Logger::instance()->log(ss.str());
  cout << ss.str() << endl;

  return NULL;
}
