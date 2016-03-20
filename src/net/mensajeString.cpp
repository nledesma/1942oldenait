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
