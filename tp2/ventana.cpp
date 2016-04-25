#include "ventana.hpp"
#include <list>

Ventana::Ventana(int ancho, int alto){
	this->ancho = ancho;
	this->alto = alto;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "Hubo un error para iniciar la ventana: " <<  SDL_GetError() << endl;
		//TODO acá habría que loggear el error y agarrarlo con una excepcion
	}
	else{
		//Se crea la ventana
		window = SDL_CreateWindow( "1942", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->ancho, this->alto, SDL_WINDOW_SHOWN );
		if(window == NULL){
			cout << "Hubo un error: " << SDL_GetError() << endl;
			//TODO acá habría que loggear el error y agarrarlo con una excepcion
		}else{
			//Superficie de la ventana
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	//TODO todo esto deberia estar encapsulado en alguna funcion o algo, porque sino aparece muchas veces!
	gVentanaRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(gVentanaRenderer == NULL){
		cout << "No se pudo crear el renderer de la ventana, SDL Error: " <<  SDL_GetError() << endl;
	}else{
		//Initialize renderer color
		SDL_SetRenderDrawColor(gVentanaRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
}
bool Ventana::iniciarElementos(){
	bool success = true;
	//TODO los parametros vienen del xml
	Escenario* escenario = new Escenario(800, 600);
	//TODO a futuro deberia recibir las cosas del xml
	//TODO habria que hacer un and de las demas cosas..
	cout << "ESTOY POR LLEGAR A LEVANTAR LA PUTA IMAGEN" << endl;
	success = escenario->iniciar(gVentanaRenderer, "espacio.bmp");
	cout << "LEVANTE LA PUTA IMAGEN" << endl;
	//Apply the image
	cout << "ESTO ES EL FONDO " << escenario->getImagenFondo() << endl;
	SDL_BlitSurface(escenario->getImagenFondo(), NULL, screenSurface, NULL );
	//Update the surface
	SDL_UpdateWindowSurface(window);

	return success;
}

void Ventana::cerrar(){
	gTexturaVentana.free();
	SDL_DestroyRenderer(gVentanaRenderer);
	//Deallocate surface
	SDL_FreeSurface(imagenFondo);
	imagenFondo = NULL;
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

/*int Ventana::iniciar(){
	//Start up SDL and create window
	if(this == NULL){
		cout << "Hubo un error al crear la ventana" << endl;
		//TODO excepcion
		return 0;
	}else{
		//Load media
		if(!this->cargarImagenDeFondo()){
			cout << "Fallo el cargar imagen de fondo" << endl;
			return 0;
		}else{
			//Main loop flag
			bool salir = false;
			//Event handler
			SDL_Event eventoVentana;
			//While application is running
			while(!salir){
				//Handle events on queue
				while(SDL_PollEvent(&eventoVentana) != 0){
					//User requests quit
					if(eventoVentana.type == SDL_QUIT){
						salir = true;
					}
				}
				//Apply the image
				SDL_BlitSurface(imagenFondo, NULL, screenSurface, NULL );
				//Update the surface
				SDL_UpdateWindowSurface(window);
			}
		}
	}
	//Free resources and close SDL
	this->cerrar();
	return 1;
}*/

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

SDL_Renderer* Ventana::getVentanaRenderer(){
	return this->gVentanaRenderer;
}

ContenedorTextura Ventana::getVentanaTextura(){
	return this->gTexturaVentana;
}
