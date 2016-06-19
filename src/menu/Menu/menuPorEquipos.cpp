#include "menuPorEquipos.hpp"
MenuPorEquipos::MenuPorEquipos(Ventana* ventana){
    this->botonSiguiente = new Boton();
    this->fondo = new Figura();
    this->texto = NULL;
    this->lista = new ListaDeSeleccion(ventana, 100, 150);
}

void MenuPorEquipos::cargarBotones(Ventana* ventana){
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
    this->texto = new Texto(30, AMARILLO_STAR_WARS, STAR_WARS_FONT, ventana);
    this->texto->cargarFuente("SELECCIONE UN EQUIPO");

}

void MenuPorEquipos::renderizar(Ventana* ventana){
    this->fondo->render(0, 0, ventana->getVentanaRenderer());
    this->getBotonSiguiente()[0].render(ventana->getVentanaRenderer());
    this->texto->renderCentrado(120);
    this->lista->renderizar();
}

Boton* MenuPorEquipos::getBotonSiguiente(){
    return this->botonSiguiente;
}

ListaDeSeleccion* & MenuPorEquipos::getListaDeSeleccion(){
    return this->lista;
}

void MenuPorEquipos::cerrar(){
    this->getBotonSiguiente()->getFigura()->free();
    delete this->lista;
}
