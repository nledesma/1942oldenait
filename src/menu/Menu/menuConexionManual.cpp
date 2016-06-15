#include "menuConexionManual.hpp"
MenuConexionManual::MenuConexionManual(){
     this->botonSiguiente = new BotonSiguiente();
     this->botonAtras = new BotonAtras();
     this->textoIP = NULL;
     this->fondo = new Figura();
}

void MenuConexionManual::cargarBotones(Ventana* ventana){
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")) {
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }
    if (!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloSiguiente" ))){
        cout << "No se ha podido cargar la textura del boton!" << endl;
    } else {
        this->getBotonSiguiente()->setSprites(ventana->getVentanaRenderer());
        this->botonSiguiente[0].setPosition(450, 400);
    }
    if(!(this->botonAtras->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloAtras"))){
        cout << "No se ha podido cargar la textura del boton!" << endl;
    }else{
        this->getBotonAtras()->setSprites(ventana->getVentanaRenderer());
        this->botonAtras[0].setPosition(150, 450);
    }

    this->textoIP = new Texto(35, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    this->textoIP->cargarFuente("INGRESE IP: ");
}

void MenuConexionManual::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->getBotonAtras()[0].render(ventana->getVentanaRenderer());
    this->textoIP->renderizar(160, 150);
}

BotonSiguiente* MenuConexionManual::getBotonSiguiente(){
    return this->botonSiguiente;
}

BotonAtras* MenuConexionManual::getBotonAtras(){
    return this->botonAtras;
}

void MenuConexionManual::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
    this->getBotonAtras()->getFigura()->free();
    this->textoIP->getFigura()->free();
}
