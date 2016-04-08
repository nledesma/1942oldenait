#include "mensaje.hpp"
// POR ahí podría recibir char array, que viene del xml.
Mensaje::Mensaje(int tipo, string id, string valor){
  set(tipo, id, valor);
}

void Mensaje::set(int tipo, string id, string valor){
  this->tipo = tipo;
  this->id = id;
  this->valor = valor;
}

Mensaje::Mensaje(infoMensaje datos, char* contenido){
  set(datos, contenido);
}

void Mensaje::set(infoMensaje datos, char* contenido){
  // El contenido el id y el valor concatenados.
  tipo = datos.tipo;
  // Ahora separamos el contenido.
  string id(contenido, datos.longitudId);
  string valor(contenido, datos.longitudId, datos.longitudValor);

  this->id = id;
  this->valor = valor;
}

string Mensaje::getId(){
  return id;
}

string Mensaje::getValor(){
  return valor;
}

int Mensaje::getTipo(){
  return tipo;
}

string Mensaje::strTipo(){
  if (tipo == T_STRING) return "STRING";
  if (tipo == T_CHAR) return "CHAR";
  if (tipo == T_INT) return "INT";
  if (tipo == T_DOUBLE) return "DOUBLE";
  return "ERROR";
}

const char *Mensaje::codificar(){
  string bytes = "";
  bytes += (char) tipo;
  pushearInt(bytes, id.length());
  pushearInt(bytes, valor.length());
  bytes += id + valor;
  return bytes.c_str();
}


infoMensaje Mensaje::decodificarInfo(char *pInfoMensaje){
  infoMensaje informacion;
	informacion.tipo = (int) pInfoMensaje[0];
	memcpy(& informacion.longitudId, pInfoMensaje + 1, INT_SIZE);
	memcpy(& informacion.longitudValor, pInfoMensaje + 1 + INT_SIZE, INT_SIZE);
	return informacion;
}

// TODO sacar estas dos funciones de mensaje.
void Mensaje::pushearInt(string &str, int n){
  char bytes[INT_SIZE];
  //memcopy
  memcpy((void*)bytes, (void*)&n, INT_SIZE);

  for (unsigned int i = 0 ; i < INT_SIZE; i++){
    str += bytes[i];
  }
}

int Mensaje::lengthId(){
  return id.length();
}

int Mensaje::lengthValor(){
  return valor.length();
}

void Mensaje::imprimirBytes(const char *bytes, int n){
  for (int i = 0; i < n; i++){
    cout << (int) bytes[i] << " ";
  }
  cout << endl;
}

Mensaje::~Mensaje(){}
