#include "menuModosDeJuego.hpp"
MenuModosDeJuego::MenuModosDeJuego(){
     this->botonEnColaboracion = new BotonEnColaboracion();
     this->botonPorEquipos = new BotonPorEquipos();
     this->botonModoPractica = new BotonModoPractica();
     this->fuenteModos = NULL;
     this->figuraFuenteModos = new Figura();
}

bool MenuModosDeJuego::cargarBotones(Ventana* ventana){
    bool success = true;
    if(!(this->botonEnColaboracion->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/enColaboracionSprite.png"))){
		cout << "Failed to load button sprite texture!" << endl;
		success = false;
    }else{
        //Set sprites
        this->getBotonEnColaboracion()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonEnColaboracion[0].setPosition(210, 200);
    }
    if(!(this->botonPorEquipos->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(),"../../resources/img/SpritesBotones/porEquiposSprite.png"))){
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    }else{
        //Set sprites
        this->getBotonPorEquipos()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonPorEquipos[0].setPosition(210, 260);
    }
    if(!(this->botonModoPractica->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/modoPracticaSprite.png"))){
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    }else{
        //Set sprites
        this->getBotonModoPractica()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonModoPractica[0].setPosition(210, 320);
    }
    SDL_Color colorNegro2 = { 0, 0, 0 };
    this->fuenteModos = TTF_OpenFont("../../resources/fonts/STARWARS.ttf",30);
    this->getFiguraFuenteModosDeJuego()->loadFromRenderedText("Elija un modo de juego: ", colorNegro2, fuenteModos, ventana->getVentanaRenderer());

    return success;
}

void MenuModosDeJuego::renderizar(Ventana* ventana){
    this->getBotonEnColaboracion()[0].render(ventana->getVentanaRenderer());
    this->getBotonPorEquipos()[0].render(ventana->getVentanaRenderer());
    this->getBotonModoPractica()[0].render(ventana->getVentanaRenderer());
    this->getFiguraFuenteModosDeJuego()->renderMenu(ventana->getVentanaRenderer(), 100, 150, NULL, 0, NULL, (SDL_RendererFlip)NULL);
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
