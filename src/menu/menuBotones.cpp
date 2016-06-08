#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Menu/menuPrincipal.hpp"
#include "Menu/menuModosDeJuego.hpp"
#include "Menu/menuDatosDeUsuario.hpp"
#include "ventana.hpp"
using namespace std;

void cargarMenuModosDeJuego(Ventana* ventana, MenuModosDeJuego* menuModosDeJuego){
	bool quit = false;
	SDL_Event e;
	while( !quit ){
		while( SDL_PollEvent( &e ) != 0 ){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			menuModosDeJuego->getBotonEnColaboracion()[0].handleEvent(&e);
			menuModosDeJuego->getBotonPorEquipos()[0].handleEvent(&e);
			menuModosDeJuego->getBotonModoPractica()[0].handleEvent(&e);
		}
		ventana->limpiar();
		//Renderizar
		ventana->renderizarFondo();
		menuModosDeJuego->renderizar(ventana);
		SDL_RenderPresent(ventana->getRenderer());
	}
	menuModosDeJuego->cerrar();
}

void cargarMenuDatosDeUsuario(Ventana* ventana, MenuDatosDeUsuario* menuDatosDeUsuario, char* &alias){
	MenuModosDeJuego* menuModosDeJuego = new MenuModosDeJuego();
	int i = 0;
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while(SDL_PollEvent( &e ) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			int respuesta2 = menuDatosDeUsuario->getBotonSiguiente()[0].handleEvent(&e);
			if(respuesta2 == 1){
				cout << "ABRIR MENU MODOS DE JUEGO" << endl;
				menuDatosDeUsuario->cerrar();
				menuModosDeJuego->cargarBotones(ventana);
				cargarMenuModosDeJuego(ventana, menuModosDeJuego);
			}
			ventana->limpiar();
			//Renderizado del fondo
			ventana->renderizarFondo();
			//TODO esto podria ir encapsulado en otra funcion.
			if (e.type == SDL_KEYDOWN){
				alias[i] = e.key.keysym.sym;
				i++;
				//Update swcreen
				SDL_Color colorNegro = { 0, 0, 0 };
				TTF_Font* fuenteAlias = menuDatosDeUsuario->getFuenteAlias();
				fuenteAlias = TTF_OpenFont("Fuentes/STARWARS.ttf",25);
				menuDatosDeUsuario->getFiguraFuenteAlias()->loadFromRenderedText(alias, colorNegro, fuenteAlias, ventana->getRenderer());
			}
		}
		ventana->limpiar();
		//Renderizado
		ventana->renderizarFondo();
		menuDatosDeUsuario->renderizar(ventana);
		SDL_RenderPresent(ventana->getRenderer());
	}
}

int main(int argc, char* args[]){
	Ventana* ventana = new Ventana(640, 480);
	char* alias = new char[10];
	MenuPrincipal* menuPrincipal = new MenuPrincipal();
	MenuDatosDeUsuario* menuDatosDeUsuario = new MenuDatosDeUsuario();

	if(!ventana->iniciar()){
		cout << "No se ha podido inicializar la ventana!"  << endl;
	}else{
		ventana->cargarFondo();
		//TODO esto de cargar los botones deberia ir en un if-else.
		menuPrincipal->cargarBotones(ventana);
		bool quit = false;
		SDL_Event e;
		while(!quit){
			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_QUIT){
					quit = true;
				}
				int respuesta = menuPrincipal->getBotonJugar()[0].handleEvent(&e);
				if(respuesta == 1){
					menuPrincipal->cerrar();
					//Arranca el menu de datos del usuario.
					menuDatosDeUsuario->cargarBotones(ventana);
					cargarMenuDatosDeUsuario(ventana, menuDatosDeUsuario, alias);
				}
				int respuestaSalir = menuPrincipal->getBotonSalir()[0].handleEvent(&e);
				if(respuestaSalir == 1){
					menuPrincipal->cerrar();
					ventana->cerrar();
					return 0;
				}
				ventana->limpiar();
				//Renderizado
				ventana->renderizarFondo();
    			menuPrincipal->renderizar(ventana);
				SDL_RenderPresent(ventana->getRenderer());
			}
		}
		menuDatosDeUsuario->cerrar();
	}
	//Free y cerrado de SDL
	menuPrincipal->cerrar();
	ventana->cerrar();
	return 0;
}
