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
	int scrollingOffset = 0;
	Avion* avion = new Avion();
	Elemento* elemento = new Elemento(100, 300);
	Elemento* elemento2 = new Elemento(600, 400);
	this->ventana->iniciar();
	this->fondoEscenario->loadFromFile(path, ventana->getVentanaRenderer());
	this->fondoEscenario->render(0,0,ventana->getVentanaRenderer());
	SDL_RenderPresent(ventana->getVentanaRenderer());
	avion->cargarImagen("honguito.bmp",ventana->getVentanaRenderer());
	this->cargarElemento(elemento, ventana->getVentanaRenderer(), "planet.bmp");
	this->cargarElemento(elemento2, ventana->getVentanaRenderer(), "asteroide.bmp");

	bool quit = false;
	SDL_Event e;
	Temporizador temporizador;
	while(!quit){
		while( SDL_PollEvent( &e ) != 0 ){
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			avion->manejarEvento(e);
		}
		//TODO ver lo de que avance con el tipo, esto parece que no hay que hacerlo ahora (?)
		//this->iniciarCamara(avion);
		float timeStep = temporizador.getTicks() / 1000.f;
		//TODO VER LO DE RENDER PRESENT
		//Scroll background
		++scrollingOffset;
		if(scrollingOffset > this->fondoEscenario->getWidth()){
			scrollingOffset = 0;
		}
		temporizador.comenzar();
		SDL_SetRenderDrawColor(ventana->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(ventana->getVentanaRenderer());
		this->fondoEscenario->render(0,0,ventana->getVentanaRenderer());
		//Render background
		this->fondoEscenario->render(0, scrollingOffset, ventana->getVentanaRenderer());
		this->fondoEscenario->render(0, scrollingOffset - this->fondoEscenario->getWidth(), ventana->getVentanaRenderer());

		avion->render(ventana->getVentanaRenderer());
		elemento->render(ventana->getVentanaRenderer());
		elemento2->render(ventana->getVentanaRenderer());
		avion->mover(timeStep);
		SDL_RenderPresent(ventana->getVentanaRenderer());
	}
	return 1;
}

void Escenario::cargarElemento(Elemento* elemento, SDL_Renderer* renderer, string path){
	this->agregarElemento(elemento);
	elemento->cargarImagen(path ,renderer);

}

void Escenario::agregarElemento(Elemento* elemento){
	//Agrega el elemento a la lista.
	this->elementos.push_back(elemento);

}

void Escenario::iniciarCamara(Avion* avion){
	SDL_Rect camara = { 0, 0, 800, 600};
	//Center the camara over the dot
	//TODO ver lo de pasar los numeros, que los devuelva un metodo
	camara.x = (avion->getPosicionX() + Avion::AVION_ANCHO / 2 ) - 800 / 2;
	camara.y = (avion->getPosicionY() + Avion::AVION_ALTO / 2 ) - 600 / 2;
	//Keep the camara in bounds
	if( camara.x < 0 ){
		camara.x = 0;
	}
	if( camara.y < 0 ){
		camara.y = 0;
	}
	if( camara.x > LEVEL_WIDTH - camara.w ){
		camara.x = LEVEL_WIDTH - camara.w;
	}
	if( camara.y > LEVEL_HEIGHT - camara.h ){
		camara.y = LEVEL_HEIGHT - camara.h;
	}
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
