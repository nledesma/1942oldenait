#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include "mensaje.hpp"

// Esto tendría en un .h de constantes.
#define T_STRING 0
#define T_INT 1
#define T_DOUBLE 2
#define T_CHAR 3

using namespace std;

Mensaje::Mensaje(int unId, string unValor, int unTipo) {
	id = unId;
	tipo = unTipo;
	//TODO template!
	switch (tipo) {
		case T_STRING:{
			string* val = new string();
			(*val) = unValor;
			valor = (void*) val;
			break;
		}
		case T_INT:{
			int *val = new int();
			(*val) = atoi(unValor.c_str());
			valor = (void*) val;
			break;}
		case T_DOUBLE:{
			double *val = new double();
			(*val) = atof(unValor.c_str());
			valor = (void*) val;
			break;}
		case T_CHAR:{
			char *val = new char();
			(*val) = unValor[0];
			valor = (void*) val;
			break;}
	}

}

void Mensaje::setId(int unId) {
	id = unId;
}

int Mensaje::getId() {
	return id;
}

void Mensaje::setValor(void* unValor) {
	valor = unValor;
}

void* Mensaje::getValor() {
	return valor;
}


int Mensaje::getTipo(){
	return tipo;
}

void Mensaje::setTipo(int unTipo) {
	tipo = unTipo;
}

string Mensaje::devolverTipo(){
	switch (this->tipo) {
		case T_STRING:{
			return "string";
			break;
		}
		case T_INT:{
			return "int";
			break;
		}
		case T_DOUBLE:{
			return "double";
			break;
			}
		case T_CHAR:{
			return "char";
			break;
		}
		default:{
			cout << "flasheaste" << endl;
			break;
		}
	}
}


Mensaje::~Mensaje(){
	// Borrado sin clase.
	switch (tipo) {
		case T_STRING:{
			delete (string*) valor;
			break;
		}
		case T_INT:{
			delete(int*) valor;
			break;
		}
		case T_DOUBLE:{
			delete (double*) valor;
			break;
			}
		case T_CHAR:{
			delete (char*) valor;
			break;
		}
	}
}
