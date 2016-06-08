#include "menuPrincipal.hpp"
MenuPrincipal::MenuPrincipal(){
     this->botonJugar = new BotonJugar();
     this->botonSalir = new BotonSalir();
     this->texto = NULL;
     this->fondo = new Figura();
}

bool MenuPrincipal::cargarBotones(Ventana* ventana){
    bool success = true;
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/estrellas.png")) {
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }
    if (!(this->botonJugar->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/jugarSprite.png" ))){
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    } else {
        //Set sprites
        this->getBotonJugar()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonJugar[0].setPosition(250, 300);
    }


    if (!(this->botonSalir->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/salirSprite.png"))){
		cout << "Failed to load button sprite texture!" << endl;
		success = false;
    } else {
        //Set sprites
        this->getBotonSalir()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSalir[0].setPosition(250, 370);
    }
    //Agrego a partir de aca
    SDL_Color color = { 255, 232, 32 };
    this->texto = new Texto(50, color, ventana);
    this->texto->cargarFuente("1942 OLDENAIT");

    return success;
}

void MenuPrincipal::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonJugar()[0].render(ventana->getVentanaRenderer());
    this->getBotonSalir()[0].render(ventana->getVentanaRenderer());
    this->texto->renderizar(160, 150);
}

BotonJugar* MenuPrincipal::getBotonJugar(){
     return this->botonJugar;
}

BotonSalir* MenuPrincipal::getBotonSalir(){
    return this->botonSalir;
}

void MenuPrincipal::cerrar(){
	//Free loaded images
    this->getBotonJugar()->getFigura()->free();
    this->getBotonSalir()->getFigura()->free();
    this->texto->getFigura()->free();
}