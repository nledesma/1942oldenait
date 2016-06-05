#include "../src/menu/listaDeSeleccion.hpp"
#include "../src/juego/vista/ventana.hpp"
int main(){
    Ventana ventana(800, 800);
    ListaDeSeleccion lista(&ventana);
    ventana.iniciar();
    bool quit = false;
	SDL_Event e;

    lista.agregarOpcion("Opcion 1");
    lista.agregarOpcion("Opcion 2");
    lista.agregarOpcion("Opcion 3");

    while( !quit ){
		while( SDL_PollEvent( &e ) != 0 ){
			if(e.type == SDL_QUIT){
				quit = true;
			}
		}
        ventana.limpiar();
        lista.renderizar();
        SDL_RenderPresent(ventana.getVentanaRenderer());

    }
    ventana.cerrar();
    return 0;
}
