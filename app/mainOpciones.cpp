#include "../src/menu/listaDeSeleccion.hpp"
#include "../src/juego/vista/ventana.hpp"
int main(){
    Ventana* ventana = new Ventana(800, 800);
    ListaDeSeleccion lista;
    ventana->iniciar();
    bool quit = false;
	SDL_Event e;

    lista.agregarOpcion("Opcion 1", ventana->getVentanaRenderer());
    lista.agregarOpcion("Opcion 2", ventana->getVentanaRenderer());
    lista.agregarOpcion("Opcion 3", ventana->getVentanaRenderer());

    while( !quit ){
		while( SDL_PollEvent( &e ) != 0 ){
			if(e.type == SDL_QUIT){
				quit = true;
			}
		}
        ventana->limpiar();
        //Renderizar
        lista.renderizar(ventana->getVentanaRenderer());
        SDL_RenderPresent(ventana->getVentanaRenderer());

    }
    ventana->cerrar();
    return 0;
}
