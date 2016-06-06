#include "menuConexiones.hpp"
MenuConexiones::MenuConexiones(){
    this->botonSiguiente = new BotonSiguiente();
    this->fondo = new Figura();
}

bool MenuConexiones::cargarBotones(Ventana* ventana){
    bool success = true;
    if(!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/espacio.png")){
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }

    if(!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/siguienteSprite.png"))){
		cout << "Failed to load button sprite texture!" << endl;
		success = false;
    }else{
        //Set sprites
        this->getBotonSiguiente()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSiguiente[0].setPosition(350, 550);
    }


    return success;
}

void MenuConexiones::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    // this->getFiguraFuenteAlias()->renderMenu(ventana->getVentanaRenderer(), (800 - this->getFiguraFuenteAlias()->getWidth()) / 2, (800 - this->getFiguraFuenteAlias()->getHeight()) / 2, NULL, 0, NULL, (SDL_RendererFlip)NULL);
}

BotonSiguiente* MenuConexiones::getBotonSiguiente(){
    return this->botonSiguiente;
}

void MenuConexiones::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
	//Quit SDL subsystems
    // TTF_Quit();
	// IMG_Quit();
	// SDL_Quit();
}
