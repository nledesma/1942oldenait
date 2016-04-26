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
	avion->cargarImagen("honguito.bmp",ventana->getVentanaRenderer());
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while( SDL_PollEvent( &e ) != 0 ){
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		//TODO VER LO DE RENDER PRESENT
		avion->manejarEvento(e);
		avion->mover();
		SDL_SetRenderDrawColor(ventana->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(ventana->getVentanaRenderer());
		this->fondoEscenario->render(0,0,ventana->getVentanaRenderer());
		avion->render(ventana->getVentanaRenderer());
	}
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
