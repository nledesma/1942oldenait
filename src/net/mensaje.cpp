#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include "mensaje.hpp"

using namespace std;

Mensaje::Mensaje() {
	// id = unId;
	// tipo = unTipo;
	// //TODO template!
	// switch (tipo) {
	// 	case T_STRING:{
	// 		string* val = new string();
	// 		(*val) = unValor;
	// 		valor = (void*) val;
	// 		break;
	// 	}
	// 	case T_INT:{
	// 		int *val = new int();
	// 		(*val) = atoi(unValor.c_str());
	// 		valor = (void*) val;
	// 		break;}
	// 	case T_DOUBLE:{
	// 		double *val = new double();
	// 		(*val) = atof(unValor.c_str());
	// 		valor = (void*) val;
	// 		break;}
	// 	case T_CHAR:{
	// 		char *val = new char();
	// 		(*val) = unValor[0];
	// 		valor = (void*) val;
	// 		break;}
	// }

}

void Mensaje::setId(int unId) {
	id = unId;
}

int Mensaje::getId() {
	return id;
}

// Mensaje::~Mensaje(){
// 	// Borrado sin clase.
// 	switch (tipo) {
// 		case T_STRING:{
// 			delete (string*) valor;
// 			break;
// 		}
// 		case T_INT:{
// 			delete(int*) valor;
// 			break;
// 		}
// 		case T_DOUBLE:{
// 			delete (double*) valor;
// 			break;
// 			}
// 		case T_CHAR:{
// 			delete (char*) valor;
// 			break;
// 		}
// 	}
// }
