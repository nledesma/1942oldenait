#include "menuPrincipal.hpp"

MenuPrincipal::MenuPrincipal(Ventana * ventana): Menu(ventana) {
     this->botonJugar = new BotonJugar();
     this->botonSalir = new BotonSalir();
     this->titulo = new Figura();
     this->anterior = this;
     this->siguiente = NULL;
}

void MenuPrincipal::cerrar(){
    botonJugar->getFigura()->free();
    botonSalir->getFigura()->free();
    this->titulo->free();
}

void MenuPrincipal::cargarBotones() {
    if (!(this->botonJugar->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloJugar" ))) {
        cout << "No se ha podido cargar la textura del boton!" << endl;
    } else {
        botonJugar->setSprites(ventana->getVentanaRenderer());
        this->botonJugar->setPosition(300, 400);
    }

    if (!(this->botonSalir->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloSalir"))) {
		cout << "No se ha podido cargar la textura del boton!" << endl;
    } else {
        botonSalir->setSprites(ventana->getVentanaRenderer());
        this->botonSalir->setPosition(300, 470);
    }

    this->titulo->loadFromFilePNG(ventana->getVentanaRenderer(), "letrasMenu");

}

void MenuPrincipal::setMenuDatosUsuario(Menu * m) {
    this->siguiente = m;
}

void MenuPrincipal::render() {
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->titulo->render(100, 90, ventana->getVentanaRenderer());
    botonJugar->render(ventana->getVentanaRenderer());
    botonSalir->render(ventana->getVentanaRenderer());
}

int MenuPrincipal::manejarEvento(SDL_Event * e) {
    // TODO ver que manejarEvento sea bool.
    if (esSalida(e) || botonSalir->manejarEvento(e)) {
        return SALIR;
    }
    if (esTecla(e,SDLK_RETURN) || botonJugar->manejarEvento(e)) {
        return SIGUIENTE;
    }
    return NADA;
}

void MenuPrincipal::accionAnterior() {}
void MenuPrincipal::accionSiguiente() {}
