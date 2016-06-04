#include "menuModosDeJuego.hpp"
MenuModosDeJuego::MenuModosDeJuego(){
     this->botonEnColaboracion = new BotonEnColaboracion();
     this->botonPorEquipos = new BotonPorEquipos();
     this->botonModoPractica = new BotonModoPractica();
     this->fuenteModos = NULL;
     this->figuraFuenteModos = new Figura();
     this->fondo = new Figura();
     this->texto = NULL;
}

bool MenuModosDeJuego::cargarBotones(Ventana* ventana){
    bool success = true;
    if(!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/espacio.png")){
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }

    if(!(this->botonEnColaboracion->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/enColaboracionSprite.png"))){
		cout << "Failed to load button sprite texture!" << endl;
		success = false;
    }else{
        //Set sprites
        this->getBotonEnColaboracion()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonEnColaboracion[0].setPosition(280, 320);
    }
    if(!(this->botonPorEquipos->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(),"../../resources/img/SpritesBotones/porEquiposSprite.png"))){
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    }else{
        //Set sprites
        this->getBotonPorEquipos()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonPorEquipos[0].setPosition(280, 380);
    }
    if(!(this->botonModoPractica->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/modoPracticaSprite.png"))){
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    }else{
        //Set sprites
        this->getBotonModoPractica()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonModoPractica[0].setPosition(280, 440);
    }
    SDL_Color colorNegro = { 0, 0, 0 };
    this->texto = new Texto(30, colorNegro);
    this->texto->cargarFuente("Elija un modo de juego: ", ventana);
    //this->fuenteModos = TTF_OpenFont("../../resources/fonts/STARWARS.ttf",30);
    //this->getFiguraFuenteModosDeJuego()->loadFromRenderedText("Elija un modo de juego: ", colorNegro2, fuenteModos, ventana->getVentanaRenderer());

    return success;
}

void MenuModosDeJuego::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonEnColaboracion()[0].render(ventana->getVentanaRenderer());
    this->getBotonPorEquipos()[0].render(ventana->getVentanaRenderer());
    this->getBotonModoPractica()[0].render(ventana->getVentanaRenderer());
    //this->getFiguraFuenteModosDeJuego()->renderMenu(ventana->getVentanaRenderer(), 200, 210, NULL, 0, NULL, (SDL_RendererFlip)NULL);
    this->texto->renderizar(200, 210, ventana->getVentanaRenderer());
}

TTF_Font* MenuModosDeJuego::getFuenteModosDeJuego(){
    return this->fuenteModos;
}

Figura* MenuModosDeJuego::getFiguraFuenteModosDeJuego(){
    return this->figuraFuenteModos;
}

BotonEnColaboracion* MenuModosDeJuego::getBotonEnColaboracion(){
     return this->botonEnColaboracion;
}

BotonPorEquipos* MenuModosDeJuego::getBotonPorEquipos(){
     return this->botonPorEquipos;
}

BotonModoPractica* MenuModosDeJuego::getBotonModoPractica(){
     return this->botonModoPractica;
}

void MenuModosDeJuego::cerrar(){
	//Free loaded images
    this->getBotonEnColaboracion()->getFigura()->free();
    this->getBotonPorEquipos()->getFigura()->free();
    this->getBotonModoPractica()->getFigura()->free();
    //TODO liberar textura de la fuente.
    TTF_CloseFont(fuenteModos);
    this->fuenteModos = NULL;
	//Destroy window
	// SDL_DestroyRenderer(this->getVentana()->getVentanaRenderer());
	// SDL_DestroyWindow(this->getVentana()->getWindow());
	// this->getVentana()->cerrar();
	//Quit SDL subsystems
    // TTF_Quit();
	//IMG_Quit();
	//SDL_Quit();
}
