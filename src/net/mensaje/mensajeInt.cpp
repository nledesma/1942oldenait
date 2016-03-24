#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "mensajeInt.hpp"
using namespace std;

MensajeInt::MensajeInt(int unId, string unValor):Mensaje() {
	id = unId;
  valor = atoi(unValor.c_str());
}

void MensajeInt::setValor(int unValor) {
	valor = unValor;
}

int MensajeInt::getValor() {
	return valor;
}

int MensajeInt::getTipo(){
	return T_INT;
}

void MensajeInt::setTipo(int unTipo) {
	tipo = unTipo;
}

// Devuelve la string
string MensajeInt::strTipo(){
		return "int";
}

string MensajeInt::strValor(){
	ostringstream sstream;
	sstream << valor;
	string varAsString = sstream.str();
	return varAsString;
}

const char * MensajeInt::codificar(){
	string bytes = "";
	// Tipo
	bytes += (char) T_INT;

	pushearInt(bytes, sizeof(int));

	pushearInt(bytes, id);

	pushearInt(bytes, valor);

	return bytes.c_str();

}
