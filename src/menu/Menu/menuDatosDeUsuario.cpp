#include "menuDatosDeUsuario.hpp"
MenuDatosDeUsuario::MenuDatosDeUsuario(){
    this->botonSiguiente = new BotonSiguiente();
    this->fondo = new Figura();
     this->texto = NULL;
}

bool MenuDatosDeUsuario::cargarBotones(Ventana* ventana){
    cout << "esta por cargar el fondo en datos de usuario" << endl;
    bool success = true;
    if(!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")){
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }

    if(!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/siguienteSprite"))){
		cout << "Failed to load button sprite texture!" << endl;
		success = false;
    }else{
        //Set sprites
        this->getBotonSiguiente()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSiguiente[0].setPosition(350, 450);
    }

    SDL_Color color = { 255, 232, 32 };
    this->texto = new Texto(30, color, STAR_WARS_FONT, ventana);
    this->texto->cargarFuente("INGRESE UN ALIAS: ");

    return success;
}

void MenuDatosDeUsuario::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->texto->renderizar(200, 250);
}

BotonSiguiente* MenuDatosDeUsuario::getBotonSiguiente(){
    return this->botonSiguiente;
}

void MenuDatosDeUsuario::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
    this->texto->getFigura()->free();
}
