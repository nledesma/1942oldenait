#include "menuPrincipal.hpp"
MenuPrincipal::MenuPrincipal(){
     this->botonJugar = new BotonJugar();
     this->botonSalir = new BotonSalir();
     this->texto = NULL;
     this->fondo = new Figura();
}

void MenuPrincipal::cargarBotones(Ventana* ventana){
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")) {
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }
    if (!(this->botonJugar->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloJugar" ))){
        cout << "Failed to load button sprite texture!" << endl;
    } else {
        //Set sprites
        this->getBotonJugar()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonJugar[0].setPosition(250, 300);
    }


    if (!(this->botonSalir->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloSalir"))){
		cout << "Failed to load button sprite texture!" << endl;
    } else {
        //Set sprites
        this->getBotonSalir()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSalir[0].setPosition(250, 370);
    }
    SDL_Color color = { 255, 232, 32 };
    this->texto = new Texto(50, color, STAR_WARS_FONT, ventana);
    this->texto->cargarFuente("1942 OLDENAIT");
}

void MenuPrincipal::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonJugar()[0].render(ventana->getVentanaRenderer());
    this->getBotonSalir()[0].render(ventana->getVentanaRenderer());
    this->texto->renderCentrado(150);
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
    this->texto->getFigura()->free();
}
