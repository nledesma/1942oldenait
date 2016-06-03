#include "menuDatosDeUsuario.hpp"
MenuDatosDeUsuario::MenuDatosDeUsuario(){
    this->fuenteAlias = NULL;
    this->fuenteTitulo = NULL;
    this->figuraFuenteAlias = new Figura();
    this->figuraFuenteTitulo = new Figura();
    this->botonSiguiente = new BotonSiguiente();
}

bool MenuDatosDeUsuario::cargarBotones(Ventana* ventana){
    bool success = true;
    if(!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/siguienteSprite.png"))){
		cout << "Failed to load button sprite texture!" << endl;
		success = false;
    }else{
        //Set sprites
        this->getBotonSiguiente()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSiguiente[0].setPosition(210, 300);
    }
    //Agrego a partir de aca
    SDL_Color colorNegro2 = { 0, 0, 0 };
    fuenteTitulo = TTF_OpenFont("../..../../resources/fonts/STARWARS.ttf",30);
    if(fuenteTitulo == NULL){
        cout << "NO SE PUDO CARGAR LA FUENTE" << endl;
    }
    this->getFiguraFuenteTitulo()->loadFromRenderedText("Ingrese un alias: ", colorNegro2, fuenteTitulo, ventana->getVentanaRenderer());

    return success;
}

void MenuDatosDeUsuario::renderizar(Ventana* ventana){
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    //SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    this->getFiguraFuenteTitulo()->renderMenu(ventana->getVentanaRenderer(), 100, 150, NULL, 0, NULL, (SDL_RendererFlip)NULL);
    this->getFiguraFuenteAlias()->renderMenu(ventana->getVentanaRenderer(), (800 - this->getFiguraFuenteAlias()->getWidth()) / 2, (800 - this->getFiguraFuenteAlias()->getHeight()) / 2, NULL, 0, NULL, (SDL_RendererFlip)NULL);
}

BotonSiguiente* MenuDatosDeUsuario::getBotonSiguiente(){
    return this->botonSiguiente;
}

TTF_Font* MenuDatosDeUsuario::getFuenteAlias(){
    return this->fuenteAlias;
}

TTF_Font* MenuDatosDeUsuario::getFuenteTitulo(){
    return this->fuenteTitulo;
}

Figura* MenuDatosDeUsuario::getFiguraFuenteAlias(){
    return this->figuraFuenteAlias;
}

Figura* MenuDatosDeUsuario::getFiguraFuenteTitulo(){
    return this->figuraFuenteTitulo;
}

void MenuDatosDeUsuario::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
    this->figuraFuenteAlias->free();
	this->figuraFuenteTitulo->free();
	TTF_CloseFont(fuenteAlias);
	TTF_CloseFont(fuenteTitulo);
	fuenteAlias = NULL;
	fuenteTitulo = NULL;
	//Quit SDL subsystems
    // TTF_Quit();
	// IMG_Quit();
	// SDL_Quit();
}
