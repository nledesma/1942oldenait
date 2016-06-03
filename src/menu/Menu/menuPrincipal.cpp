#include "menuPrincipal.hpp"
MenuPrincipal::MenuPrincipal(){
     this->botonJugar = new BotonJugar();
     this->botonSalir = new BotonSalir();
     this->textoUsuario = NULL;
     this->figuraTextoUsuario = new Figura();
}

bool MenuPrincipal::cargarBotones(Ventana* ventana){
    bool success = true;
    if(!(this->botonJugar->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/jugarSprite.png" ))){
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    }else{
        //Set sprites
        this->getBotonJugar()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonJugar[0].setPosition(210, 200);
    }


    if(!(this->botonSalir->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/salirSprite.png"))){
		cout << "Failed to load button sprite texture!" << endl;
		success = false;
    }else{
        //Set sprites
        this->getBotonSalir()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSalir[0].setPosition(210, 260);
    }
    //Agrego a partir de aca
    SDL_Color colorNegro2 = { 0, 0, 0 };
    this->textoUsuario = TTF_OpenFont("../../resources/fonts/STARWARS.ttf",50);
    this->getFiguraTextoUsuario()->loadFromRenderedText("1942 OLDENAIT", colorNegro2, textoUsuario, ventana->getVentanaRenderer());

    return success;
}

void MenuPrincipal::renderizar(Ventana* ventana){
    this->getBotonJugar()[0].render(ventana->getVentanaRenderer());
    this->getBotonSalir()[0].render(ventana->getVentanaRenderer());
    this->getFiguraTextoUsuario()->renderMenu(ventana->getVentanaRenderer(), 100, 120, NULL, 0, NULL, (SDL_RendererFlip)NULL);
}

BotonJugar* MenuPrincipal::getBotonJugar(){
     return this->botonJugar;
}

BotonSalir* MenuPrincipal::getBotonSalir(){
    return this->botonSalir;
}

TTF_Font * MenuPrincipal::getTextoUsuario(){
    return this->textoUsuario;
}

Figura* MenuPrincipal::getFiguraTextoUsuario(){
    return this->figuraTextoUsuario;
}

void MenuPrincipal::cerrar(){
	//Free loaded images
    this->getBotonJugar()->getFigura()->free();
    this->getBotonSalir()->getFigura()->free();
    this->getFiguraTextoUsuario()->free();

    //Free global font
	TTF_CloseFont(this->getTextoUsuario());
	this->textoUsuario = NULL;

	//Destroy window
	// SDL_DestroyRenderer(this->getVentana()->getVentanaRenderer());
	// SDL_DestroyWindow(this->getVentana()->getWindow());
	// this->getVentana()->cerrar();
	//Quit SDL subsystems
    //TTF_Quit();
	//IMG_Quit();
	//SDL_Quit();
}
