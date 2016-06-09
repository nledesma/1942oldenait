#include "menuModosDeJuego.hpp"
MenuModosDeJuego::MenuModosDeJuego(){
     this->botonEnColaboracion = new BotonEnColaboracion();
     this->botonPorEquipos = new BotonPorEquipos();
     this->botonModoPractica = new BotonModoPractica();
     this->fondo = new Figura();
     this->texto = NULL;
}

bool MenuModosDeJuego::cargarBotones(Ventana* ventana){
    bool success = true;
    // TODO constantes para los sprites de estos métodos.
    if (!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/estrellas.png")) {
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }

    if (!(this->botonEnColaboracion->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/enColaboracionSprite.png"))) {
		cout << "Failed to load button sprite texture!" << endl;
		success = false;
    } else {
        //Set sprites
        this->getBotonEnColaboracion()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonEnColaboracion[0].setPosition(280, 320);
    }

    if (!(this->botonPorEquipos->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(),"../../resources/img/SpritesBotones/porEquiposSprite.png"))) {
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    } else {
        //Set sprites
        this->getBotonPorEquipos()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonPorEquipos[0].setPosition(280, 380);
    }

    if (!(this->botonModoPractica->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "../../resources/img/SpritesBotones/modoPracticaSprite.png"))) {
        cout << "Failed to load button sprite texture!" << endl;
        success = false;
    } else {
        //Set sprites
        this->getBotonModoPractica()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonModoPractica[0].setPosition(280, 440);
    }

    SDL_Color color = { 255, 232, 32 };
    this->texto = new Texto(30, color, STAR_WARS_FONT, ventana);
    this->texto->cargarFuente("ELIJA UN MODO DE JUEGO: ");

    return success;
}

void MenuModosDeJuego::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonEnColaboracion()[0].render(ventana->getVentanaRenderer());
    this->getBotonPorEquipos()[0].render(ventana->getVentanaRenderer());
    this->getBotonModoPractica()[0].render(ventana->getVentanaRenderer());
    this->texto->renderizar(200, 210);
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
    this->getBotonEnColaboracion()->getFigura()->free();
    this->getBotonPorEquipos()->getFigura()->free();
    this->getBotonModoPractica()->getFigura()->free();
}
