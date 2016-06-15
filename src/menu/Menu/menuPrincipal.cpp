#include "menuPrincipal.hpp"
MenuPrincipal::MenuPrincipal(){
     this->botonJugar = new BotonJugar();
     this->botonSalir = new BotonSalir();
     this->figuraLetras = new Figura();
     this->fondo = new Figura();
}

void MenuPrincipal::cargarBotones(Ventana* ventana){
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")) {
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }
    if (!(this->botonJugar->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloJugar" ))){
        cout << "No se ha podido cargar la textura del boton!" << endl;
    } else {
        this->getBotonJugar()->setSprites(ventana->getVentanaRenderer());
        this->botonJugar[0].setPosition(300, 400);
    }


    if (!(this->botonSalir->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloSalir"))){
		cout << "No se ha podido cargar la textura del boton!" << endl;
    } else {
        this->getBotonSalir()->setSprites(ventana->getVentanaRenderer());
        this->botonSalir[0].setPosition(300, 470);
    }
    this->figuraLetras->loadFromFilePNG(ventana->getVentanaRenderer(), "letrasMenu");

}

void MenuPrincipal::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->figuraLetras->render(100, 90, ventana->getVentanaRenderer());
    this->getBotonJugar()[0].render(ventana->getVentanaRenderer());
    this->getBotonSalir()[0].render(ventana->getVentanaRenderer());
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
}
