#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include "mensajeString.hpp"

using namespace std;

MensajeString::MensajeString(int unId, string unValor):Mensaje() {
	id = unId;
  valor = unValor;
}

MensajeString::MensajeString(infoMensaje datos, char * unValor):Mensaje() {
	id = datos.id;
	tipo = datos.tipo;
	valor = string(unValor);
	cout << valor << endl;
}

void MensajeString::setValor(string unValor) {
	valor = unValor;
}

string MensajeString::getValor() {
	return valor;
}

int MensajeString::getTipo(){
	return T_STRING;
}

void MensajeString::setTipo(int unTipo) {
	tipo = unTipo;
}

// Devuelve la string
string MensajeString::strTipo(){
		return "string";
}

string MensajeString::strValor(){
		return valor;
}
const char * MensajeString::codificar(){
	string bytes = "";
	// Tipo
	bytes += (char) T_STRING;

	pushearInt(bytes, valor.length());

	pushearInt(bytes, id);

	bytes += valor;
	cout << "El mensaje actualmente tiene "<< bytes.length() << " bytes" << endl;
	imprimirBytes(bytes.c_str(), bytes.length());

	return bytes.c_str();
}

int MensajeString::lengthValor() {
	return valor.length();
}