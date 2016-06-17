#include "menuConexionPuerto.hpp"
MenuConexionPuerto::MenuConexionPuerto(){
     this->botonSiguiente = new Boton();
     this->textoPuerto = NULL;
     this->fondo = new Figura();
}

void MenuConexionPuerto::cargarBotones(Ventana* ventana){
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")) {
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }
    if (!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloSiguiente" ))){
        cout << "Failed to load button sprite texture!" << endl;

    } else {
        //Set sprites
        this->getBotonSiguiente()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSiguiente[0].setPosition(450, 400);
    }

    SDL_Color color = { 255, 232, 32 };
    this->textoPuerto = new Texto(35, color,  STAR_WARS_FONT, ventana);
    this->textoPuerto->cargarFuente("INGRESE PUERTO: ");

}

void MenuConexionPuerto::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->textoPuerto->renderizar(160, 150);
}

Boton* MenuConexionPuerto::getBotonSiguiente(){
    return this->botonSiguiente;
}

void MenuConexionPuerto::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
    this->textoPuerto->getFigura()->free();
}
