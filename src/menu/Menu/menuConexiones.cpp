#include "menuConexiones.hpp"
MenuConexiones::MenuConexiones(Ventana* ventana){
    this->botonSiguiente = new BotonSiguiente();
    this->fondo = new Figura();
    this->lista = new ListaDeSeleccion(ventana, 100, 150);
}

bool MenuConexiones::cargarBotones(Ventana* ventana){
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

    return success;
}

void MenuConexiones::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->lista->renderizar();
}

BotonSiguiente* MenuConexiones::getBotonSiguiente(){
    return this->botonSiguiente;
}

ListaDeSeleccion* & MenuConexiones::getListaDeSeleccion(){
    return this->lista;
}

void MenuConexiones::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
    delete this->lista;
}
