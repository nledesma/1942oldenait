#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "mensaje.hpp"

using namespace std;

Mensaje::Mensaje(){}

void Mensaje::setId(int unId) {
	id = unId;
}

int Mensaje::getId() {
	return id;
}

// TODO por qué no se puede descomentar esto?
Mensaje::~Mensaje(){}

void Mensaje::pushearInt(string &str, int n){
	char bytes[INT_SIZE];
	//memcopy
	memcpy((void*)bytes, (void*)&n, INT_SIZE);

	for (unsigned int i = 0 ; i < INT_SIZE; i++){
		str += bytes[i];
	}
}

void Mensaje::pushearDouble(string &str, int n){
	char bytes[DOUBLE_SIZE];
	//memcopy
	memcpy((void*)bytes, (void*)&n, DOUBLE_SIZE);

	for (unsigned int i = 0 ; i < DOUBLE_SIZE; i++){
		str += bytes[i];
	}
}

infoMensaje Mensaje::decodificarInfo(char * pInfoMensaje){
	infoMensaje informacion;
	informacion.tipo = (int) pInfoMensaje[0];
	informacion.longitud = (pInfoMensaje[1] << 24) + (pInfoMensaje[2] << 16) + (pInfoMensaje[3] << 8) + pInfoMensaje[4];
	informacion.id = (pInfoMensaje[5] << 24) + (pInfoMensaje[6] << 16) + (pInfoMensaje[7] << 8) + pInfoMensaje[8];
	return informacion;
}

void imprimirBytes(const char *bytes, int n){
	for (int i = 0; i < n; i++){
		cout << (int) bytes[i] << endl;
	}
}
