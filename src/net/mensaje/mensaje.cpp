#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
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
char * Mensaje::intToBytes(int n){


	//int tamInt = sizeof(int);
	int tamInt = INT_SIZE;
	char * bytes = new char[tamInt];

	for (int i = 0; i < tamInt; i++){
		bytes[i] = (n >> 8*(tamInt - (i+1))) & 0xFF;
	}

	return bytes;
}

void Mensaje::pushearInt(string &str, int n){
	char * bytes = intToBytes(n);
	for (unsigned int i = 0 ; i < INT_SIZE; i++){
		str += bytes[i];
	}
	delete []bytes;
}

void Mensaje::pushearDouble(string &str, int n){
	char * bytes = intToBytes(n);
	for (unsigned int i = 0 ; i < DOUBLE_SIZE; i++){
		str += bytes[i];
	}
	delete []bytes;
}
