#include "escenario.hpp"
using namespace std;

Escenario::Escenario(int ancho, int alto, Ventana* ventana){
	this->ancho = ancho;
	this->alto = alto;
	this->ventana = ventana;
}

Escenario::~Escenario(){}

int Escenario::getAncho(){
	return this->ancho;
}

int Escenario::getAlto(){
	return this->alto;
}

Ventana* Escenario::getVentana(){
	return this->ventana;
}

list<Avion*> Escenario::getAviones(){
	return this->aviones;
}

void Escenario::agregarAvion(Avion* avion){
	this->aviones.push_back(avion);
}
