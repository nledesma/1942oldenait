#include "../src/menu/listaDeSeleccion.hpp"
#include "../src/juego/vista/ventana.hpp"
int main(){
    Ventana ventana(800, 800);
    ventana.iniciar();

    ListaDeSeleccion* lista = new ListaDeSeleccion(&ventana);

    lista->agregarOpcion("Opcion 1");
    lista->agregarOpcion("Opcion 2");
    lista->agregarOpcion("Opcion 3");

    bool quit = false;
    SDL_Event e;

    while( !quit ){
		while( SDL_PollEvent( &e ) != 0 ){
			if(e.type == SDL_QUIT) {
				quit = true;
			}
		}
        ventana.limpiar();
        lista->renderizar();
        SDL_RenderPresent(ventana.getVentanaRenderer());
    }

    delete lista;
    ventana.cerrar();
    return 0;
}
