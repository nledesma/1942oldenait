#include "menuConexionManual.hpp"
MenuConexionManual::MenuConexionManual(){
     this->botonSiguiente = new BotonSiguiente();
     this->textoIP = NULL;
     this->textoPuerto = NULL;
     this->fondo = new Figura();
}

bool MenuConexionManual::cargarBotones(Ventana* ventana){
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

    this->textoIP = new Texto(35, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    this->textoIP->cargarFuente("INGRESE IP: ");
    // this->textoPuerto = new Texto(35, color, ventana);
    // this->textoPuerto->cargarFuente("INGRESE PUERTO: ");

    return success;
}

void MenuConexionManual::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->textoIP->renderizar(160, 150);
    // this->textoPuerto->renderizar(260, 250);
}

BotonSiguiente* MenuConexionManual::getBotonSiguiente(){
    return this->botonSiguiente;
}

void MenuConexionManual::cerrar(){
	//Free loaded images
    this->getBotonSiguiente()->getFigura()->free();
    this->textoIP->getFigura()->free();
    // this->textoPuerto->getFigura()->free();
}
