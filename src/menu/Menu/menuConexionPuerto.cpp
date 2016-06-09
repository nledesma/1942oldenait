#include "menuConexionPuerto.hpp"
MenuConexionPuerto::MenuConexionPuerto(){
     this->botonSiguiente = new BotonSiguiente();
     this->textoPuerto = NULL;
     this->fondo = new Figura();
}

bool MenuConexionPuerto::cargarBotones(Ventana* ventana){
    bool success = true;
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/estrellas.png")) {
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }
    if (!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/siguienteSprite.png" ))){
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    } else {
        //Set sprites
        this->getBotonSiguiente()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSiguiente[0].setPosition(450, 400);
    }

    SDL_Color color = { 255, 232, 32 };
    this->textoPuerto = new Texto(35, color, ventana);
    this->textoPuerto->cargarFuente("INGRESE PUERTO: ");

    return success;
}

void MenuConexionPuerto::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->textoPuerto->renderizar(160, 150);
}

BotonSiguiente* MenuConexionPuerto::getBotonSiguiente(){
    return this->botonSiguiente;
}

void MenuConexionPuerto::cerrar(){
	//Free loaded images
    this->getBotonSiguiente()->getFigura()->free();
    this->textoPuerto->getFigura()->free();
}
