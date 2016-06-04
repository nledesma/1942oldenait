#include "menuDatosDeUsuario.hpp"
MenuDatosDeUsuario::MenuDatosDeUsuario(){
    this->fuenteAlias = NULL;
    this->fuenteTitulo = NULL;
    this->figuraFuenteAlias = new Figura();
    this->figuraFuenteTitulo = new Figura();
    this->botonSiguiente = new BotonSiguiente();
    this->fondo = new Figura();
}

bool MenuDatosDeUsuario::cargarBotones(Ventana* ventana){
    cout << "esta por cargar el fondo en datos de usuario" << endl;
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
        this->botonSiguiente[0].setPosition(350, 450);
    }
    //TODO hacer con el Texto.
    SDL_Color colorNegro2 = { 0, 0, 0 };
    fuenteTitulo = TTF_OpenFont("../../resources/fonts/STARWARS.ttf",30);
    if(fuenteTitulo == NULL){
        cout << "NO SE PUDO CARGAR LA FUENTE" << endl;
    }
    this->getFiguraFuenteTitulo()->loadFromRenderedText("Ingrese un alias: ", colorNegro2, fuenteTitulo, ventana->getVentanaRenderer());

    return success;
}

void MenuDatosDeUsuario::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->getFiguraFuenteTitulo()->renderMenu(ventana->getVentanaRenderer(), 200, 250, NULL, 0, NULL, (SDL_RendererFlip)NULL);
    // this->getFiguraFuenteAlias()->renderMenu(ventana->getVentanaRenderer(), (800 - this->getFiguraFuenteAlias()->getWidth()) / 2, (800 - this->getFiguraFuenteAlias()->getHeight()) / 2, NULL, 0, NULL, (SDL_RendererFlip)NULL);
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
