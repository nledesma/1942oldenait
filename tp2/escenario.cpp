#include "escenario.hpp"
using namespace std;

Escenario::Escenario(int ancho, int alto){
	this->ancho = ancho;
	this->alto = alto;
	cout << "ancho: " << ancho << " alto: " << alto << endl;
	this->ventana = new Ventana(ancho, alto);
	this->fondoEscenario = new Figura();
}

Escenario::~Escenario(){}

int Escenario::iniciar(string path){
	float scrollingOffset = 0;
	//Avion* avion = new Avion();
	this->ventana->iniciar();
	this->fondoEscenario->loadFromFile(path, ventana->getVentanaRenderer());
	this->fondoEscenario->render(0,0,ventana->getVentanaRenderer(), NULL);
	SDL_RenderPresent(ventana->getVentanaRenderer());
	//avion->cargarImagen("millenium-sprite.bmp",ventana->getVentanaRenderer());
	incluirAviones();
	incluirElementos();

	bool quit = false;
	SDL_Event e;
	Temporizador temporizador;
	while(!quit){
		while( SDL_PollEvent( &e ) != 0 ){
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			this->getAviones().front()->manejarEvento(e, ventana->getVentanaRenderer());
		}
		//TODO ver lo de que avance con el tipo, esto parece que no hay que hacerlo ahora (?)
		//this->iniciarCamara(avion);
		float timeStep = temporizador.getTicks() / 1000.f;
		//TODO VER LO DE RENDER PRESENT
		//Scroll background
		scrollingOffset = scrollingOffset + 0.2;
		if(scrollingOffset > this->fondoEscenario->getWidth()){
			scrollingOffset = 0;
		}
		temporizador.comenzar();
		SDL_SetRenderDrawColor(ventana->getVentanaRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(ventana->getVentanaRenderer());
		this->fondoEscenario->render(0,0,ventana->getVentanaRenderer(), NULL);
		//Render background
		this->fondoEscenario->render(0, scrollingOffset, ventana->getVentanaRenderer(), NULL);
		this->fondoEscenario->render(0, scrollingOffset - this->fondoEscenario->getWidth(), ventana->getVentanaRenderer(), NULL);

		renderizarElementos(ventana->getVentanaRenderer());
		renderizarAviones(ventana->getVentanaRenderer());
		//avion->render(ventana->getVentanaRenderer());
		this->getAviones().front()->mover(timeStep);
		this->getAviones().front()->renderDisparos(ventana->getVentanaRenderer());
		this->getAviones().front()->moverDisparos(timeStep);
		SDL_RenderPresent(ventana->getVentanaRenderer());
	}
	return 1;
}

void Escenario::incluirAviones(){
	string path;
	for(list<Avion*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
		Avion* avion = *iterador;
		path = (avion->getIdSprite() + ".bmp").c_str();
		this->cargarAvion(avion, ventana->getVentanaRenderer(),path);
	}

}

void Escenario::cargarAvion(Avion* avion, SDL_Renderer* renderer, string path){
		avion->cargarImagen(path, renderer);
}

void Escenario::cargarElemento(Elemento* elemento, SDL_Renderer* renderer, string path){
	elemento->cargarImagen(path ,renderer);

}

void Escenario::agregarElemento(string spriteId, float posX, float posY){
	//Agrega el elemento a la lista.
	Elemento* elemento = new Elemento(posX, posY, spriteId);
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

list<Avion*>& Escenario::getAviones(){
	return this->aviones;
}

void Escenario::agregarAvion(float velocidadDesplazamiento, float velocidadDisparos, string avionSpriteId, string vueltaSpriteId, string disparosSpriteId){
	Avion* avion = new Avion(velocidadDesplazamiento, velocidadDisparos, avionSpriteId, vueltaSpriteId, "redLaserRay.bmp");
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

Ventana* Escenario::getVentana(){
	return this->ventana;
}

const char* Escenario::getFondoSprite(){
	const char* fondo = "galaxia";
	return fondo;
}

int Escenario::getAnchoFondo(){
	return this->ancho;
}

int Escenario::getAltoFondo(){
	return this->alto;
}

list<Elemento*>& Escenario::getElementos(){
	return this->elementos;
}

void Escenario::incluirElementos(){
	string path;
	for(list<Elemento*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
		Elemento* elemento = *iterador;
		path = (elemento->getSpriteId() + ".bmp").c_str();
		this->cargarElemento(elemento, ventana->getVentanaRenderer(),path);
		//this->cargarElemento(elemento2, ventana->getVentanaRenderer(), "asteroide.bmp");
	}
}

void Escenario::renderizarElementos(SDL_Renderer* renderer){
	for(list<Elemento*>::iterator iterador = this->getElementos().begin(); iterador != this->getElementos().end(); ++iterador){
		Elemento* elemento = *iterador;
		elemento->render(renderer);
	}
}

void Escenario::renderizarAviones(SDL_Renderer* renderer){
	for(list<Avion*>::iterator iterador = this->getAviones().begin(); iterador != this->getAviones().end(); ++iterador){
		Avion* avion = *iterador;
		avion->render(renderer);
	}
}
