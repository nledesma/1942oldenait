#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include "mensajeChar.hpp"

using namespace std;

MensajeChar::MensajeChar(int unId, string unValor):Mensaje() {

	id = unId;
  valor = unValor[0];
}

void MensajeChar::setValor(char unValor) {
	valor = unValor;
}

char MensajeChar::getValor() {
	return valor;
}

int MensajeChar::getTipo(){
	return T_CHAR;
}

void MensajeChar::setTipo(int unTipo) {
	tipo = unTipo;
}

// Devuelve la string
string MensajeChar::strTipo(){
		return "char";
}

string MensajeChar::strValor(){
	char arr[ ] = {valor, '\0'};
	return string(arr);
}
