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

MensajeChar::MensajeChar(infoMensaje datos, char* valor):Mensaje(){
	id = datos.id;
	tipo = datos.tipo;
	valor = *valor;
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

const char * MensajeChar::codificar(){
	string bytes = "";
	// Tipo
	bytes += (char) T_CHAR;

	pushearInt(bytes, 1);

	pushearInt(bytes, id);

	bytes += valor;

	return bytes.c_str();
}
