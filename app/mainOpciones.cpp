#include "../src/menu/listaDeSeleccion.hpp"
#include "../src/juego/vista/ventana.hpp"
int main(){
    Ventana ventana(800, 800);
    ventana.iniciar();

    ListaDeSeleccion* lista = new ListaDeSeleccion(&ventana, 100, 100);

    lista->agregarOpcion("Opcion 1");
    lista->agregarOpcion("Opcion 2");
    lista->agregarOpcion("Opcion 3");

    bool quit = false;
    SDL_Event e;
    int x, y; // Para los clicks.

    while( !quit ){
		while( SDL_PollEvent( &e ) != 0 ){
			if(e.type == SDL_QUIT) {
				quit = true;
			} else if(e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState( &x, &y );
                lista->clickEn(x, y);
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
