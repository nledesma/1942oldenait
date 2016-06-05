#include "menuPrincipal.hpp"
MenuPrincipal::MenuPrincipal(){
     this->botonJugar = new BotonJugar();
     this->botonSalir = new BotonSalir();
     this->texto = NULL;
    //  this->textoUsuario = NULL;
    //  this->figuraTextoUsuario = new Figura();
     this->fondo = new Figura();
}

bool MenuPrincipal::cargarBotones(Ventana* ventana){
    bool success = true;
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/espacio.png")) {
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
    SDL_Color colorNegro = { 0, 0, 0 };
    this->texto = new Texto(50, colorNegro, ventana);
    this->texto->cargarFuente("1942 OLDENAIT");

    // this->textoUsuario = TTF_OpenFont("../../resources/fonts/STARWARS.ttf",50);
    // if(!this->textoUsuario){
    //     cout << "No se pudo cargar la fuente: " << TTF_GetError() << endl;
    // }else{
    //     this->getFiguraTextoUsuario()->loadFromRenderedText("1942 OLDENAIT", colorNegro2, textoUsuario, ventana->getVentanaRenderer());
    // }

    return success;
}

void MenuPrincipal::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonJugar()[0].render(ventana->getVentanaRenderer());
    this->getBotonSalir()[0].render(ventana->getVentanaRenderer());
    //this->getFiguraTextoUsuario()->renderMenu(ventana->getVentanaRenderer(), 160, 150, NULL, 0, NULL, (SDL_RendererFlip)NULL);
    this->texto->renderizar(160, 150);
}

BotonJugar* MenuPrincipal::getBotonJugar(){
     return this->botonJugar;
}

BotonSalir* MenuPrincipal::getBotonSalir(){
    return this->botonSalir;
}

// TTF_Font * MenuPrincipal::getTextoUsuario(){
//     return this->textoUsuario;
// }
//
// Figura* MenuPrincipal::getFiguraTextoUsuario(){
//     return this->figuraTextoUsuario;
// }

void MenuPrincipal::cerrar(){
	//Free loaded images
    this->getBotonJugar()->getFigura()->free();
    this->getBotonSalir()->getFigura()->free();
    // this->getFiguraTextoUsuario()->free();

    //Free global font

    //TODO estas dos lineas deben ir en el destructor del texto.
	//TTF_CloseFont(this->getTextoUsuario());
    //this->textoUsuario = NULL;

	//Destroy window
	// SDL_DestroyRenderer(this->getVentana()->getVentanaRenderer());
	// SDL_DestroyWindow(this->getVentana()->getWindow());
	// this->getVentana()->cerrar();
	//Quit SDL subsystems
    //TTF_Quit();
	//IMG_Quit();
	//SDL_Quit();
}
