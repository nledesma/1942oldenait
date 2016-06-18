#include "manejadorDeMenues.hpp"

ManejadorDeMenues::ManejadorDeMenues(Ventana * ventana) {
    this->ventana = ventana;
}

void ManejadorDeMenues::menuAnterior() {
    actual->accionAnterior();
    actual = actual->getAnterior();
}

void ManejadorDeMenues::menuSiguiente() {
    actual->accionSiguiente();
    actual = actual->getSiguiente();
}

void ManejadorDeMenues::renderLoop() {
    dibujar = true;
    SDL_Event e;
    while (dibujar) {
        while (SDL_PollEvent(&e) != 0) {
            this->manejarEvento(actual->manejarEvento(&e));
            // TODO habría que ver si se hace algún chequeo acá.
        }
        actual->render();
        SDL_RenderPresent(ventana->getVentanaRenderer());
    }
}

void ManejadorDeMenues::finalizarRender() {
    dibujar = false;
}

void ManejadorDeMenues::manejarEvento(int evento) {
    switch (evento) {
        case ANTERIOR: menuAnterior(); break;
        case SIGUIENTE: menuSiguiente(); break;
        case SALIR: finalizarRender(); break;
        default: cout << "Evento no válido ("<< evento <<")." << endl;
    }
}
