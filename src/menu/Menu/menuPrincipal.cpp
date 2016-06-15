#include "menuPrincipal.hpp"
MenuPrincipal::MenuPrincipal(){
     this->botonJugar = new BotonJugar();
     this->botonSalir = new BotonSalir();
     //this->texto = NULL;
     this->figuraLetras = new Figura();
     this->fondo = new Figura();
}

void MenuPrincipal::cargarBotones(Ventana* ventana){
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")) {
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }
    if (!(this->botonJugar->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloJugar" ))){
        cout << "Failed to load button sprite texture!" << endl;
    } else {
        this->getBotonJugar()->setSprites(ventana->getVentanaRenderer());
        this->botonJugar[0].setPosition(300, 400);
    }


    if (!(this->botonSalir->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloSalir"))){
		cout << "Failed to load button sprite texture!" << endl;
    } else {
        this->getBotonSalir()->setSprites(ventana->getVentanaRenderer());
        this->botonSalir[0].setPosition(300, 470);
    }
    this->figuraLetras->loadFromFilePNG(ventana->getVentanaRenderer(), "letrasMenu");
    // SDL_Color color = { 255, 232, 32 };
    // this->texto = new Texto(50, color, STAR_WARS_FONT, ventana);
    // this->texto->cargarFuente("1942 OLDENAIT");
}

void MenuPrincipal::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->figuraLetras->render(100, 90, ventana->getVentanaRenderer());
    this->getBotonJugar()[0].render(ventana->getVentanaRenderer());
    this->getBotonSalir()[0].render(ventana->getVentanaRenderer());
    // this->texto->renderCentrado(150);
}

BotonJugar* MenuPrincipal::getBotonJugar(){
     return this->botonJugar;
}

BotonSalir* MenuPrincipal::getBotonSalir(){
    return this->botonSalir;
}

void MenuPrincipal::cerrar(){
    this->getBotonJugar()->getFigura()->free();
    this->getBotonSalir()->getFigura()->free();
    this->figuraLetras->free();
    // this->texto->getFigura()->free();
}
