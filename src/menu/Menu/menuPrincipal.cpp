#include "menuPrincipal.hpp"

MenuPrincipal::MenuPrincipal(Ventana * ventana): Menu(ventana) {
     this->botonJugar = new Boton();
     this->botonSalir = new Boton();
     this->titulo = new Figura();
     this->anterior = this;
     this->siguiente = NULL;
     cargarBotones();
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
    Menu::render();
    titulo->render(100, 90, ventana->getVentanaRenderer());
    botonJugar->render(ventana->getVentanaRenderer());
    botonSalir->render(ventana->getVentanaRenderer());
}

int MenuPrincipal::manejarEvento(SDL_Event * e) {
    if (esSalida(e) || botonSalir->manejarEvento(e) == BOTON_APRETADO || esTecla(e, SDLK_ESCAPE)) {
        return SALIR;
    }
    if (esTecla(e,SDLK_RETURN) || botonJugar->manejarEvento(e) == BOTON_APRETADO) {
        return SIGUIENTE;
    }
    return NADA;
}

void MenuPrincipal::accionAnterior() {}
void MenuPrincipal::accionSiguiente() {}
