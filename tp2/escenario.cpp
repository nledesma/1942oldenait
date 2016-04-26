#include "escenario.hpp"
using namespace std;

Escenario::Escenario(int ancho, int alto){
	this->ancho = ancho;
	this->alto = alto;
	this->ventana = new Ventana(ancho, alto);
	this->fondoEscenario = new Figura();
}

Escenario::~Escenario(){}

int Escenario::iniciar(string path){
	Avion* avion = new Avion();
	this->ventana->iniciar();
	this->fondoEscenario->loadFromFile(path, ventana->getVentanaRenderer());
	this->fondoEscenario->render(0,0,ventana->getVentanaRenderer());
	SDL_RenderPresent(ventana->getVentanaRenderer());
	cout << "ESTA POR CARGAR LA IMAGEN" << endl;
	avion->cargarImagen("mario.bmp",ventana->getVentanaRenderer());
	cout << "CARGO LA FORRA DE LA IMAGEN " << endl;
	return 1;
}

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
	/*if(!this->getImagenFondo()->this->ventana->getVentanaRenderer()){
		cout << "NO SE HA PODIDO CARGAR LA IMAGEN DE FONDO" << endl;
		success = false;
	}*/
	return success;
}

Figura* Escenario::getFondoEscenario(){
	return this->fondoEscenario;
}
