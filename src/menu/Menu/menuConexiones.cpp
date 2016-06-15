#include "menuConexiones.hpp"
MenuConexiones::MenuConexiones(Ventana* ventana){
    this->botonSiguiente = new BotonSiguiente();
    this->botonAtras = new BotonAtras();
    this->fondo = new Figura();
    this->lista = new ListaDeSeleccion(ventana, 100, 150);
}

void MenuConexiones::cargarBotones(Ventana* ventana){
    if(!this->fondo->loadFromFilePNG(ventana->getVentanaRenderer(), "estrellas")){
        cout << "No se ha podido cargar la imagen de fondo" << endl;
    }

    if(!(this->botonSiguiente->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloSiguiente"))){
		cout << "Failed to load button sprite texture!" << endl;
    }else{
        //Set sprites
        this->getBotonSiguiente()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonSiguiente[0].setPosition(350, 450);
    }
    if(!(this->botonAtras->getFigura()->loadFromFilePNG(ventana->getVentanaRenderer(), "SpritesBotones/botonAmarilloAtras"))){
        cout << "Failed to load button sprite texture!" << endl;
    }else{
        //Set sprites
        this->getBotonAtras()->setSprites(ventana->getVentanaRenderer());
        //Setea los botones en las posiciones
        this->botonAtras[0].setPosition(150, 450);
    }


}

void MenuConexiones::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->getBotonAtras()[0].render(ventana->getVentanaRenderer());
    this->lista->renderizar();
}

BotonSiguiente* MenuConexiones::getBotonSiguiente(){
    return this->botonSiguiente;
}

BotonAtras* MenuConexiones::getBotonAtras(){
    return this->botonAtras;
}

ListaDeSeleccion* & MenuConexiones::getListaDeSeleccion(){
    return this->lista;
}

void MenuConexiones::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
    this->getBotonAtras()->getFigura()->free();
    delete this->lista;
}
