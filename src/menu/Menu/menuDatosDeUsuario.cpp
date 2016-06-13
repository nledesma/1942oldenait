#include "menuDatosDeUsuario.hpp"
MenuDatosDeUsuario::MenuDatosDeUsuario(){
    this->botonSiguiente = new BotonSiguiente();
    this->fondo = new Figura();
     this->texto = NULL;
}

void MenuDatosDeUsuario::cargarBotones(Ventana* ventana){
    if(!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")){
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }

    if(!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/siguienteSprite"))){
		cout << "Failed to load button sprite texture!" << endl;
    }else{
        //Set sprites
        this->getBotonSiguiente()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSiguiente[0].setPosition(350, 450);
    }

    SDL_Color color = { 255, 232, 32 };
    this->texto = new Texto(30, color, STAR_WARS_FONT, ventana);
    this->texto->cargarFuente("INGRESE UN ALIAS: ");
}

void MenuDatosDeUsuario::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->texto->renderCentrado(150);
}

BotonSiguiente* MenuDatosDeUsuario::getBotonSiguiente(){
    return this->botonSiguiente;
}

void MenuDatosDeUsuario::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
    this->texto->getFigura()->free();
}
