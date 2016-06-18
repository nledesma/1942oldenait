#include "menuIntermedio.hpp"

MenuIntermedio::MenuIntermedio(Ventana * ventana) : Menu(ventana) {
    this->botonSiguiente = new BotonSiguiente();
    this->botonAtras = new BotonAtras();
    cargarBotones();
}

void MenuIntermedio::cargarBotones() {
    if (!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloSiguiente"))) {
		cout << "No se ha podido cargar la textura del boton!" << endl;
    } else {
        this->botonSiguiente->setSprites(ventana->getVentanaRenderer());
        this->botonSiguiente->setPosition(400, 450);
    }

    if (!(this->botonAtras->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloAtras"))) {
        cout << "No se ha podido cargar la textura del boton!" << endl;
    } else {
        this->botonAtras->setSprites(ventana->getVentanaRenderer());
        this->botonAtras->setPosition(150, 450);
    }
}

int MenuIntermedio::manejarEvento(SDL_Event * e) {
    if (esSalida(e)) {
        return SALIR;
    }
    if (esTecla(e, SDLK_ESCAPE) || botonAtras->manejarEvento(e) == BOTON_APRETADO) {
        return ANTERIOR;
    }
    if (esTecla(e, SDLK_RETURN) || botonSiguiente->manejarEvento(e) == BOTON_APRETADO) {
        return SIGUIENTE;
    }
    return NADA;
}

void MenuIntermedio::render() {
    Menu::render();
    this->botonSiguiente->render(ventana->getVentanaRenderer());
    this->botonAtras->render(ventana->getVentanaRenderer());
}
