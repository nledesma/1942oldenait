#include "ventana.hpp"
#include <list>

Ventana::Ventana(int ancho, int alto){
	this->ancho = ancho;
	this->alto = alto;
}

int Ventana::iniciar(){
	int success = 1;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "Hubo un error para iniciar la ventana: " <<  SDL_GetError() << endl;
		//TODO acá habría que loggear el error y agarrarlo con una excepcion
	}
	else{
		//Set texture filtering to linear
		if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )){
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		//Se crea la ventana
		sdlWindow = SDL_CreateWindow( "1942", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->ancho, this->alto, SDL_WINDOW_SHOWN );
		if(sdlWindow == NULL){
			cout << "Hubo un error: " << SDL_GetError() << endl;
			//TODO acá habría que loggear el error y agarrarlo con una excepcion
		}
	}
	//TODO todo esto deberia estar encapsulado en alguna funcion o algo, porque sino aparece muchas veces!
	gVentanaRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gVentanaRenderer == NULL){
		cout << "No se pudo crear el renderer de la ventana, SDL Error: " <<  SDL_GetError() << endl;
	}else{
		//Initialize renderer color
		SDL_SetRenderDrawColor(gVentanaRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	return success;
}

void Ventana::cerrar(){
	/*gTexturaVentana.free();
	SDL_DestroyRenderer(gVentanaRenderer);
	//Deallocate surface
	SDL_FreeSurface(imagenFondo);
	imagenFondo = NULL;
	//Destroy window
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();*/
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

SDL_Renderer* Ventana::getVentanaRenderer(){
	return this->gVentanaRenderer;
}
