#include "escenario.hpp"
using namespace std;

Escenario::Escenario(int ancho, int alto){
	this->ancho = ancho;
	this->alto = alto;
	this->ventana = new Ventana(ancho, alto);
	this->fondoEscenario = new Figura();
}

Escenario::~Escenario(){}

int Escenario::getAncho(){
	return this->ancho;
}

int Escenario::getAlto(){
	return this->alto;
}

list<Avion*> Escenario::getAviones(){
	return this->aviones;
}

void Escenario::agregarAvion(Avion* avion){
	this->aviones.push_back(avion);
}


bool Escenario::cargarImagenDeFondo(SDL_Renderer* renderer){
	bool success = true;
	/*bool hola = gTexturaEscenario->loadFromFile(path, renderer);
	cout << "ESTO ES TEXTURA ESCENARIO " << hola << endl;
	if(!hola){
		cout << "Failed to load background texture image!" << endl;
		success = false;
	}*/
	return success;
}

bool Escenario::cargarImagenes(string path){
	this->path = path;
	bool success = true;
	if(!this->cargarImagenDeFondo(this->ventana->getVentanaRenderer())){
		cout << "NO SE HA PODIDO CARGAR LA IMAGEN DE FONDO" << endl;
		success = false;
	}
	return success;
}

SDL_Surface* Escenario::getImagenFondo(){
	return this->imagenFondo;
}
