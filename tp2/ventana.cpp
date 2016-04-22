#include "ventana.hpp"
#include <list>

Ventana::Ventana(){

}

string Ventana::getIdSpriteFondo(){
	return this->idSpriteFondo;
}

void Ventana::setIdSpriteFondo(string id){
	this->idSpriteFondo = id;
}

int Ventana::getAncho(){
	return this->ancho;
}

void Ventana::setAncho(int ancho){
	this->ancho = ancho;
}

int Ventana::getAlto(){
	return this->alto;
}

void Ventana::setAlto(int alto){
	this->alto = alto;
}

list <Elemento> Ventana::getElementos(){
	return this->elementos;
}

void Ventana::agregarElemento(Elemento elemento){
	this->elementos.push_back(elemento);
}
