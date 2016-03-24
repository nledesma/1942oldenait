#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "mensajeDouble.hpp"
using namespace std;

MensajeDouble::MensajeDouble(int unId, string unValor):Mensaje() {
	id = unId;
	valor = (double) (atof(unValor.c_str()));
}

void MensajeDouble::setValor(double unValor) {
	valor = unValor;
}

double MensajeDouble::getValor() {
	return valor;
}

int MensajeDouble::getTipo(){
	return T_DOUBLE;
}

void MensajeDouble::setTipo(int unTipo) {
	tipo = unTipo;
}

// Devuelve la string
string MensajeDouble::strTipo(){
		return "double";
}

string MensajeDouble::strValor(){
	ostringstream sstream;
	sstream << valor;
	string varAsString = sstream.str();
	return varAsString;
}

const char * MensajeDouble::codificar(){
	string bytes = "";
	// Tipo
	bytes += (char) T_DOUBLE;

	pushearInt(bytes, sizeof(double));

	pushearInt(bytes, id);

	pushearDouble(bytes, valor);

	return bytes.c_str();

}
