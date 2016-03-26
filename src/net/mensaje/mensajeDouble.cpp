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

MensajeDouble::MensajeDouble(infoMensaje datos, char * valor):Mensaje() {
	id = datos.id;
	tipo = datos.tipo;
	// TODO QUE ONDA ESTO. TODO 2 TODO TODO TODO codificar bien.
	valor = (datos.valor[0] << 24) + (datos.valor[1] << 16) + (datos.valor[2] << 8) + datos.valor[3]);
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
